/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:15 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 04:05:17 by theog            ###   ########.fr       */
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
	std::string _username;
public:
	int status;	
	int _client_fd;
	std::string channel_name;
	struct pollfd poll_fd;
	Client(int client_fd);
	~Client();
	// void init();
	// void sendMessage(const std::string& message);
	// std::string receiveMessage();
	//void closeClient();
};