/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/06/16 16:19:58 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client.hpp"
#include "channel.hpp"
#include "parser.hpp"
//#include <sys/epoll.h>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <fcntl.h>

class Server
{
private:
	int server_fd;                       // socket serveur
	int epoll_fd;                        // epoll file descriptor
	int port;                            // port du serveur
	const std::string password;          // mot de passe
	struct sockaddr_in server_addr;      // struct adresse serveur
	std::vector<Client*> clients;        // liste des clients connectés
	std::vector<Channel*> channels;      // liste des channels IRC

public:
	// Constructeur / Destructeur
	Server(int port, const std::string password);
	~Server();

	// Initialisation et démarrage
	void init();
	void start();

	// Connexion / gestion client
	void acceptClient();
	void handleClient(int client_fd);
	void closeClient(int client_fd);
	void removeClient(int client_fd);

	// Communication
	void Server::SendRPL(int clientSocket, const std::string &replyCode, const std::string &nickname, const std::string &message);
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);

	// Authentification
	bool check_password(std::string str);
	void get_password(Client* client);
	void get_username(Client* client);

	// Commandes / gestion des messages
	void inputs_manager(char buffer[BUFFER_SIZE], int client_fd);

	// Channels
	void addChannel(std::string name);
	void removeChannel(std::string name);
	int get_channel_index(std::string name);

	// Getters
	std::vector<Client*>& get_clients(void);
	std::vector<Channel*>& get_channels(void);
};

// Fonction utilitaire externe
Client* get_client_by_fd(std::vector<Client*>& clients, int fd);
std::string trim(const std::string& str);
