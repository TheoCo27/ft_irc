/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/12 20:27:47 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

 #include "client.hpp"
// #include "channel.hpp"

class Server
{
	int server_fd;
	int port;
	struct sockaddr_in server_addr;
	std::vector<struct pollfd> poll_fds;
	// std::vector<Client*> clients;
	// std::vector<Channel*> channels;
public:
	Server(int port);
	~Server();
	void init();
	void start();
	void acceptClient();
	void handleClient(int client_fd);
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);
	void closeClient(int client_fd);
};