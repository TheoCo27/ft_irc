/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:09 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/12 20:51:44 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

#define BUFFER_SIZE 5000
#include <algorithm>

Server::Server(int port)
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
	for (size_t i = 0; i < this->poll_fds.size(); ++i) {
		close(this->poll_fds[i].fd);
	}
	this->poll_fds.clear();
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
		int poll_count = poll(this->poll_fds.data(), this->poll_fds.size(), -1);
		if (poll_count < 0) {
			perror("poll");
			exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < this->poll_fds.size(); ++i) {
			if (this->poll_fds[i].revents & POLLIN) {
				if (this->poll_fds[i].fd == this->server_fd) {
					this->acceptClient();
				} else {
					this->handleClient(this->poll_fds[i].fd);
				}
			}
		}
	}
}		
void Server::acceptClient()
{
	int client_fd = accept(this->server_fd, NULL, NULL);
	if (client_fd >= 0) {
		std::cout << "👤 Nouveau client connecté (fd: " << client_fd << ")" << std::endl;
		struct pollfd client_poll_fd;
		client_poll_fd.fd = client_fd;
		client_poll_fd.events = POLLIN;
		client_poll_fd.revents = 0;
		this->poll_fds.push_back(client_poll_fd);
	} else {
		perror("accept");
	}
}

struct MatchClientFd {
    int client_fd;
    MatchClientFd(int fd) : client_fd(fd) {}
    bool operator()(const struct pollfd& pfd) const {
        return pfd.fd == client_fd;
    }
};

bool matchClientFd(const struct pollfd& pfd, int client_fd) {
    return pfd.fd == client_fd;
}

// auto matchClientFdWrapper(int client_fd) {
//     return [client_fd](const struct pollfd& pfd) { return pfd.fd == client_fd; };
// }

void Server::handleClient(int client_fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0) {
        std::cout << "❌ Client déconnecté (fd: " << client_fd << ")" << std::endl;
        close(client_fd);

        // Utilisation du functor pour supprimer le client
        this->poll_fds.erase(std::remove_if(this->poll_fds.begin(), this->poll_fds.end(),
            MatchClientFd(client_fd)), this->poll_fds.end());
    } 
    else {
        buffer[bytes] = '\0';
        std::cout << "📩 Reçu du client " << client_fd << " : " << buffer;
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
	if (bytes <= 0) {
		return "";
	}
	buffer[bytes] = '\0';
	return std::string(buffer);
}
void Server::closeClient(int client_fd)
{
    close(client_fd);
    this->poll_fds.erase(std::remove_if(this->poll_fds.begin(), this->poll_fds.end(),
        MatchClientFd(client_fd)), this->poll_fds.end());
}
// void Server::closeServer()
// {
// 	close(this->server_fd);
	// this->poll_fds.clear();
// }
// void Server::handlePoll()
// {
// 	int poll_count = poll(this->poll_fds.data(), this->poll_fds.size(), -1);
// 	if (poll_count < 0) {
	// 	perror("poll");
	// 	exit(EXIT_FAILURE);
	// }
	// for (size_t i = 0; i < this->poll_fds.size(); ++i) {
	// 	if (this->poll_fds[i].revents & POLLIN) {
	// 		if (this->poll_fds[i].fd == this->server_fd) {
	// 			this->acceptClient();
	// 		} else {
	// 			this->handleClient(this->poll_fds[i].fd);
	// 		}
	// 	}
	// }
// }
// void Server::handleError(const std::string& errorMessage)
// {
// 	std::cerr << "❌ Erreur : " << errorMessage << std::endl;
// 	exit(EXIT_FAILURE);
// }
// }
// void Server::handleSIGINT(int signal)
// {
// 	std::cout << "🔴 Arrêt du serveur..." << std::endl	;
	// this->closeServer();
	// exit(EXIT_SUCCESS);
// }
// }