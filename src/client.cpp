/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:06 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 16:07:00 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client(int client_fd)
{
	this->_client_fd = client_fd;
	this->poll_fd.fd = client_fd;
	this->poll_fd.events = POLLIN;
	this->poll_fd.revents = 0;
	this->_nickname = "iencli";
	this->_username = "iencli42";
	this->status = UNAUTHORIZED;
}
Client::~Client(){}


void Client::sendMessage(int client_fd, const std::string& message)
{
	send(client_fd, message.c_str(), message.size(), 0);
}

std::string Client::receiveMessage(int client_fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return "";
	buffer[bytes] = '\0';
	return std::string(buffer);
}