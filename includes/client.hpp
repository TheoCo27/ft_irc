/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:15 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/15 16:37:55 by tcohen           ###   ########.fr       */
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
	std::string _username;
	int status;	
	int _client_fd;
	std::string channel_name;
	struct pollfd poll_fd;
public:
	Client(int client_fd);
	~Client();
	//getters
	std::string getNickname() const;
	std::string getUsername() const;
	int getStatus() const;
	int getClientFd() const;
	std::string getChannelName() const;
	struct pollfd& getPollFd();
	//setters
	void setNickname(const std::string& nickname);
	void setUsername(const std::string& username);
	void setStatus(int status);
	void setClientFd(int client_fd);
	void setChannelName(const std::string& channel_name);
	void setPollFd(struct pollfd poll_fd);
	//methods
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);
	// void init();
	// void sendMessage(const std::string& message);
	// std::string receiveMessage();
	//void closeClient();
};