/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:15 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/24 10:33:08 by tcohen           ###   ########.fr       */
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
#include <cerrno>
#define BUFFER_SIZE 1024

enum ClientStatus
{
	EMPTY = 0,
	PASSWORD_OK = 1 << 2,
	USER_OK = 1 << 3,
	NICK_OK = 1 << 4,
	CONNECTED = 1 << 5,
	IN_CHANNEL = 1 << 6,
	DISCONNECTED = 1 << 7
};

class Client
{
private:
	std::string _nickname;
	std::string _username;
	std::string _realname;
	int status;	
	int _client_fd;
	std::string channel_name;
	std::vector<std::string> channel_list;
	std::string old_buf;

public:
	Client(int client_fd);
	~Client();

	// Getters
	std::string getNickname() const;
	std::string getUsername() const;
	std::string getRealname() const;
	int getStatus() const;
	int getClientFd() const;
	std::string getChannelName() const;
	std::string& getold_buf();
	std::vector<std::string> &get_channel_list();

	// Setters
	void setNickname(const std::string& nickname);
	void setUsername(const std::string& username);
	void setRealname(const std::string& realname);
	void setStatus(int status);
	void setClientFd(int client_fd);
	void setChannelName(const std::string& channel_name);
	void setOld_buf(std::string new_buf);

	// Méthodes
	void sendMessage(int client_fd, const std::string& message);
	std::string receiveMessage(int client_fd);
	void remove_channel_fromchannelList(std::string channel_name);
	std::string format_RPL(std::string msg);
};
