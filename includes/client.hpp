/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:15 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 16:59:53 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio> 
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>
#include <algorithm>
#include <sys/socket.h>
#define BUFFER_SIZE 5000

enum ClientStatus
{
	UNAUTHORIZED,
	AUTHORIZED,
	CONNECTED,
	IN_CHANNEL,
	DISCONNECTED
};

class Client
{
private:
	std::string _nickname;
public:
	std::string _username;
	int status;	
	int _client_fd;
	std::string channel_name;
	struct pollfd poll_fd;
	Client(int client_fd);
	~Client();
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);
	// void init();
	// void sendMessage(const std::string& message);
	// std::string receiveMessage();
	//void closeClient();
};