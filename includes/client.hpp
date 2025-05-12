/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:15 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/12 18:44:35 by tcohen           ###   ########.fr       */
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

class Client
{
	int client_fd;
	struct sockaddr_in client_addr;
	std::vector<struct pollfd> poll_fds;
public:
	Client(int client_fd, struct sockaddr_in client_addr);
	~Client();
	void init();
	void sendMessage(const std::string& message);
	std::string receiveMessage();
	void closeClient();
};