/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:09 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 17:01:02 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

// Functor C++98 compatible
struct MatchClientFd {
	int client_fd;
	MatchClientFd(int fd) : client_fd(fd) {}
	bool operator()(const struct pollfd& pfd) const {
		return pfd.fd == client_fd;
	}
};

struct MatchClientPtr {
	int client_fd;
	MatchClientPtr(int fd) : client_fd(fd) {}
	bool operator()(Client* c) const {
		return c->_client_fd == client_fd;
	}
};

Server::Server(int port, const std::string password) : password(password)
{
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
}

Server::~Server()
{
	close(this->server_fd);
	for (size_t i = 0; i < this->poll_fds.size(); ++i)
		close(this->poll_fds[i].fd);
	this->poll_fds.clear();
	for (size_t i = 0; i < this->clients.size(); ++i)
		delete this->clients[i];
	this->clients.clear();
}

void Server::init()
{
	struct pollfd server_poll_fd;
	server_poll_fd.fd = this->server_fd;
	server_poll_fd.events = POLLIN;
	server_poll_fd.revents = 0;
	this->poll_fds.push_back(server_poll_fd);
}

void Server::start()
{
	while (true) {
		int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
		if (poll_count < 0) {
			perror("poll");
			exit(EXIT_FAILURE);
		}

		for (size_t i = 0; i < poll_fds.size(); ++i) {
			if (poll_fds[i].revents & POLLIN) {
				if (poll_fds[i].fd == server_fd)
					acceptClient();
				else
					handleClient(poll_fds[i].fd);
			}
		}
	}
}

std::string trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \r\n\t");
	size_t end = str.find_last_not_of(" \r\n\t");
	if (start == std::string::npos || end == std::string::npos)
		return "";
	return str.substr(start, end - start + 1);
}

bool Server::check_password(std::string str)
{
	return str == this->password;
}

void Server::get_password(Client* client)
{
	sendMessage(client->_client_fd, "Please type password!\n");
	std::string to_check = trim(receiveMessage(client->_client_fd));

	if (check_password(to_check))
		client->status = AUTHORIZED;
}

void Server::get_username(Client* client)
{
	sendMessage(client->_client_fd, "Please type username!\n");
	std::string to_check = trim(receiveMessage(client->_client_fd));
	client->_username = to_check;
}

void Server::acceptClient()
{
	int client_fd = accept(this->server_fd, NULL, NULL);
	if (client_fd < 0) {
		perror("accept");
		return;
	}

	Client* client = new Client(client_fd);
	client->poll_fd.fd = client_fd;
	client->poll_fd.events = POLLIN;
	client->poll_fd.revents = 0;

	this->clients.push_back(client);
	this->poll_fds.push_back(client->poll_fd);

	get_password(client);

	if (client->status == AUTHORIZED) {
		get_username(client);
		client->status = CONNECTED;
		sendMessage(client_fd, "Welcome to the server!\n");
		std::cout << "🟢 Client connecté (fd: " << client_fd << ")" << std::endl;
	} else {
		sendMessage(client_fd, "Wrong password!\nConnexion has been closed.\n");
		closeClient(client_fd);
		removeClient(client_fd);
	}
}

void    Server::inputs_manager(char buffer[BUFFER_SIZE], int client_fd)
{
    std::string inputs(buffer);
	Client* client = get_client_by_fd(this->clients, client_fd);
    if (is_cmd(inputs))
    {
		make_command(inputs, client, this->clients, this->channels);
    }
	else if (client->status == IN_CHANNEL)
	{
		int i = get_channel_index(client->channel_name);
		channels[i]->sendMessageToAllClients(inputs, client);
	}
}

void Server::handleClient(int client_fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0) {
		std::cout << "❌ Client déconnecté (fd: " << client_fd << ")" << std::endl;
		closeClient(client_fd);
		removeClient(client_fd);
	} else {
		buffer[bytes] = '\0';
		std::cout << "📩 Reçu du client " << client_fd << " : " << buffer;
		inputs_manager(buffer, client_fd);
	}
}

void Server::sendMessage(int client_fd, const std::string& message)
{
	send(client_fd, message.c_str(), message.size(), 0);
}

std::string Server::receiveMessage(int client_fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return "";
	buffer[bytes] = '\0';
	return std::string(buffer);
}

void Server::closeClient(int client_fd)
{
	close(client_fd);
	this->poll_fds.erase(std::remove_if(this->poll_fds.begin(), this->poll_fds.end(),
		MatchClientFd(client_fd)), this->poll_fds.end());
}

void Server::removeClient(int client_fd)
{
	std::vector<Client*>::iterator it = std::find_if(this->clients.begin(), this->clients.end(), MatchClientPtr(client_fd));
	if (it != this->clients.end()) {
		delete *it;
		this->clients.erase(it);
	}
}


void Server::addChannel(std::string name)
{
	Channel *channel = new Channel(name);

	channels.push_back(channel);
}

int Server::get_channel_index(std::string name)
{
	for (size_t i = 0; i < channels.size(); ++i) 
	{
        if (channels[i] && channels[i]->getName() == name) {
            return (static_cast<int>(i));
        }
    }
    return (-1); // pas trouvé
}

void Server::removeChannel(std::string name)
{
	int index = get_channel_index(name);
    if (index == -1)
        return;
    channels.erase(channels.begin() + index);
}

Client* get_client_by_fd(std::vector<Client*>& clients, int fd) {
    std::vector<Client*>::iterator it = std::find_if(
        clients.begin(), clients.end(), MatchClientPtr(fd)
    );

    if (it != clients.end()) {
        return *it; // adresse du client trouvé
    }
    return NULL; // pas trouvé
}

std::vector<Client*> Server::get_clients(void){return (clients);}
std::vector<Channel*> Server::get_channels(void){return(channels);}