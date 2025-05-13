/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/13 22:31:32 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

 #include "client.hpp"
// #include "channel.hpp"

class Server
{
	int server_fd;
	int port;
	const std::string password;
	struct sockaddr_in server_addr;
	std::vector<struct pollfd> poll_fds;
	std::vector<Client*> clients;
	// std::vector<Channel*> channels;
public:
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
};