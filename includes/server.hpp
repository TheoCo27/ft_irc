/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 04:11:46 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

 #include "client.hpp"
 #include "channel.hpp"
 #include "parser.hpp"

#define BUFFER_SIZE 5000

class Server
{
	int server_fd;
	int port;
	const std::string password;
	struct sockaddr_in server_addr;
	std::vector<struct pollfd> poll_fds;
	std::vector<Client*> clients;
	std::vector<Channel*> channels;
public:
	std::vector<Client*> get_clients(void);
	std::vector<Channel*> get_channels(void);
	Server(int port,const std::string password);
	~Server();
	void init();
	void start();
	void acceptClient();
	void handleClient(int client_fd);
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);
	void closeClient(int client_fd);
	bool check_password(std::string str);
	void get_password(Client *client);
	void removeClient(int client_fd);
	void disconnectClient(int client_fd);
	void addChannel(std::string name);
	void removeChannel(std::string name);
	int get_channel_index(std::string name);
	void inputs_manager(char buffer[BUFFER_SIZE], int client_fd);


};

Client* get_client_by_fd(std::vector<Client*>& clients, int fd);