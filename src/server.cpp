/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:09 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/30 15:02:44 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"
#include "../includes/parser.hpp"
#include "../includes/utils.hpp"
#include <sys/epoll.h>

#define MAX_EVENTS 1024

// struct MatchClientPtr {
// 	int client_fd;
// 	MatchClientPtr(int fd) : client_fd(fd) {}
// 	bool operator()(Client* c) const {
// 		return c->getClientFd() == client_fd;
// 	}
// };

// Initialisiation du serveur

void Server::init_bot(void)
{
	this->bot->setUsername("stupid_bot");
	this->bot->setNickname("bot");
	this->bot->setRealname("from_server.42irc");
	this->bot->setStatus(this->bot->getStatus() | CONNECTED);
}

Server::Server(int port, const std::string password) : password(password) {
	this->port = port;
	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_fd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int opt = 1;
	setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&this->server_addr, 0, sizeof(this->server_addr));
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_addr.s_addr = INADDR_ANY;
	this->server_addr.sin_port = htons(this->port);

	if (bind(this->server_fd, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(this->server_fd, SOMAXCONN) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	std::cout << "🟢 Serveur IRC en écoute sur le port " << this->port << std::endl;
	bot = new Client(-1);
	init_bot();
}

Server::~Server() {
	close(this->server_fd);
	close(this->epoll_fd);
	while (!clients_map.empty()) 
		closeClient(clients_map.begin()->first);

	this->clients_map.clear();
    user_list.clear();
    nickname_list.clear();
	delete this->bot;
	for (int i = channels.size() - 1; i >= 0; --i)
		delete channels[i];
	channels.clear();
}

void Server::init() {
	this->epoll_fd = epoll_create(1);
	if (this->epoll_fd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = this->server_fd;
	if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->server_fd, &event) == -1) {
		perror("epoll_ctl: server_fd");
		exit(EXIT_FAILURE);
	}
}

void Server::start() {
	struct epoll_event events[MAX_EVENTS];

	while (true) {
		int n = epoll_wait(this->epoll_fd, events, MAX_EVENTS, -1);
		if (n == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < n; ++i) {
			if (events[i].data.fd == this->server_fd) {
				acceptClient();
			} else {
				handleClient(events[i].data.fd);
			}
		}
	}
}

static void make_socket_non_blocking(int fd) 
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

void Server::acceptClient() {
	int client_fd = accept(this->server_fd, NULL, NULL);
	if (client_fd < 0) {
		perror("accept");
		return;
	}
	make_socket_non_blocking(client_fd);
	Client* client = new Client(client_fd);
	//this->clients.push_back(client);
	this->clients_map[client_fd] = client;
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = client_fd;
	if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
		perror("epoll_ctl: client_fd");
		close(client_fd);
		return;
	}
	//sendMessage(client_fd, "Please type server password!\n");
}

bool is_msg_finished(std::string msg)
{
	if(msg.length() < 3)
		return false;
	size_t last_index = msg.length() - 1;
	if (msg[last_index] != '\n' && msg[last_index - 1] != '\r')
		return false;
	return true;
}


void Server::handleClient(int client_fd) {
	char buffer[BUFFER_SIZE];
	//Client *client = get_client_by_fd(this->clients, client_fd);
	Client *client = this->clients_map[client_fd];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0) {
		closeClient(client_fd);
		return;
	}
	buffer[bytes] = '\0';
	std::string old_buf = client->getold_buf();
	if (old_buf.empty())
		old_buf = buffer;
	else
		old_buf += buffer;
	client->setOld_buf(old_buf);
	if(is_msg_finished(old_buf) == false)
		return;
	std::string full_msg = client->getold_buf();
	//full_msg += buffer;
	client->setOld_buf("");
	std::cout << "📩 Reçu du client " << client_fd << " : " << full_msg;
	full_msg = trim(std::string(full_msg));
	inputs_manager(full_msg, client_fd);
}

// void Server::handleClient(int client_fd) {
// 	char buffer[BUFFER_SIZE];
// 	//Client *client = get_client_by_fd(this->clients, client_fd);
// 	Client *client = this->clients_map[client_fd];
// 	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
// 	if (bytes <= 0) {
// 		std::cout << "❌ Client déconnecté (fd: " << client_fd << ")" << std::endl;
// 		closeClient(client_fd);
// 		return;
// 	}
// 	buffer[bytes] = '\0';
// 	if (buffer[bytes - 1] != '\n' && buffer[bytes - 2] != '\r')
// 	{		std::string old_buf = client->getold_buf();
// 		if (old_buf.empty())
// 			old_buf = buffer;
// 		else
// 			old_buf += buffer;
// 		client->setOld_buf(old_buf);
// 		return;
// 	}
	
// 	std::string full_msg = client->getold_buf();
// 	full_msg += buffer;
// 	client->setOld_buf("");
// 	std::cout << "📩 Reçu du client " << client_fd << " : " << buffer;
// 	full_msg = trim(std::string(buffer));
// 	inputs_manager(full_msg, client_fd);
// }


void Server::closeClient(int client_fd) {
	std::cout << "❌ Client déconnecté (fd: " << client_fd << ")" << std::endl;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
	close(client_fd);
	removeClient(client_fd);
}

void Server::removeClient(int client_fd) {
	Client* client = NULL;

	if (clients_map.count(client_fd))
		client = clients_map[client_fd];
	if (!client)
		return;
    for (int i = channels.size() - 1; i >= 0; --i) {
        channels[i]->removeClient(client);
        channels[i]->remove_op(client);
		if(channels[i]->getNbClient() <= 0)
			removeChannel(channels[i]->getName());
    }
	client = clients_map[client_fd];
	remove_from_vec(this->user_list, client->getUsername());
	remove_from_vec(this->nickname_list, client->getNickname());
	this->clients_map.erase(client_fd);
	delete client;
}

void Server::sendMessage(int client_fd, const std::string& message) {
	send(client_fd, message.c_str(), message.size(), 0);
}

std::string Server::receiveMessage(int client_fd) {
	char buffer[BUFFER_SIZE];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return "";
	buffer[bytes] = '\0';
	return std::string(buffer);
}

bool Server::check_password(std::string str) {
	return str == this->password;
}

// void Server::get_password(Client* client) {
// 	sendMessage(client->getClientFd(), "Please type password!\n");
// 	std::string to_check = trim(receiveMessage(client->getClientFd()));
// 	if (check_password(to_check))
// 		client->setStatus(WAITING_USERNAME);
// }

// void Server::get_username(Client* client) {
// 	sendMessage(client->getClientFd(), "Please type username!\n");
// 	std::string to_check = trim(receiveMessage(client->getClientFd()));
// 	client->setUsername(to_check);
// 	client->setStatus(CONNECTED);
// }

void Server::inputs_manager(std::string buffer, int client_fd) {
	std::string inputs(buffer);
	if (inputs.empty())
		return;
	//Client* client = get_client_by_fd(this->clients, client_fd);
	Client* client = this->clients_map[client_fd];
	if (is_cmd(inputs)) {
		make_command(inputs, client, this);
		return;
	} 
	// else if (client->getStatus() == IN_CHANNEL) {
	// 	std::cout << "Looking for channel : " << client->getChannelName() << std::endl;
	// 	for(std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
	// 	{
	// 		Channel *chan = *it;
	// 		std::cout << chan->getName() << std::endl;
	// 	}
	// 	int i = get_channel_index(client->getChannelName());
	// 	channels[i]->sendMessageToAllClients(inputs, client);
	// }
	else
	{
		std::string reply = inputs + " :Unknown command";
		reply = format_client_reply(client, 421, reply);
		sendMessage(client_fd, reply);
	}
}

void Server::sendRPL(Client *client, int rpl_code, std::string msg)
{
	std::string reply = format_client_reply(client, rpl_code, msg);
	sendMessage(client->getClientFd(), reply);

}

void Server::sendNotice(Client *client, std::string msg)
{
	std::string reply = format_client_notice(client, msg);
	sendMessage(client->getClientFd(), reply);
}
// Client* get_client_by_fd(std::vector<Client*>& clients, int fd) {
// 	std::vector<Client*>::iterator it = std::find_if(clients.begin(), clients.end(), MatchClientPtr(fd));
// 	if (it != clients.end())
// 		return *it;
// 	return NULL;
// }

void Server::addChannel(std::string name) {
	Channel *channel = new Channel(name);
	channels.push_back(channel);
}

int Server::get_channel_index(std::string name) {
	for (size_t i = 0; i < channels.size(); ++i) {
		if (channels[i] && channels[i]->getName() == name)
			return static_cast<int>(i);
	}
	return -1;
}

void Server::removeChannel(std::string name) {
	int index = get_channel_index(name);
	if (index == -1)
		return;
	delete channels[index]; 
	channels.erase(channels.begin() + index);
}

std::map<int, Client*>& Server::get_clients_map(void) { return this->clients_map; }
std::vector<Channel*>& Server::get_channels(void) { return channels; }
std::vector<std::string>& Server::get_user_list(void){return user_list;}
std::vector<std::string>& Server::get_nickname_list(void){return nickname_list;}
Client *Server::get_bot(){return(this->bot);}


Channel *Server::get_channel_by_name(std::string channel_name)
{
	if (channel_name.empty())
		return (NULL);
	for(std::vector<Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		Channel *check = *it;
		if (check->getName() == channel_name)
			return (check);
	}
	return (NULL);
}

Client *Server::get_client_by_nick(std::string nickname)
{
	for(std::map<int, Client *>::iterator it = this->clients_map.begin(); it != this->clients_map.end(); ++it)
	{
		Client *check = it->second;
		if (check->getNickname() == nickname)
			return (check);
	}
	return (NULL);
}

std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \r\n\t");
	size_t end = str.find_last_not_of(" \r\n\t");
	if (start == std::string::npos || end == std::string::npos)
		return "";
	return str.substr(start, end - start + 1);
}



// void Server::SendRPL(int clientSocket, const std::string &replyCode, const std::string &nickname, const std::string &message) {
//     std::ostringstream response;
//     response << ":server " << replyCode << " " << nickname << " " << message << "\r\n";

//     std::string responseStr = response.str();
//     if (send(clientSocket, responseStr.c_str(), responseStr.size(), 0) == -1) {
//         std::cerr << "Failed to send reply to client: " << clientSocket << std::endl;
//     } else {
//         std::cout << "Sent: " << responseStr;
//     }
// }