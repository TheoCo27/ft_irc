/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:06 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/15 21:22:13 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client(int client_fd)
{
	this->_client_fd = client_fd;
	this->_nickname = "iencli";
	this->_username = "iencli42";
	this->status = WAITING_PASSWORD;
	this->channel_name = "";
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
//getters
std::string Client::getNickname() const{
	return this->_nickname;
}
std::string Client::getUsername() const{
	return this->_username;
}
int Client::getStatus() const{
	return this->status;
}
int Client::getClientFd() const{
	return this->_client_fd;
}
std::string Client::getChannelName() const{
	return this->channel_name;
}

//setters
void Client::setNickname(const std::string& nickname){
	this->_nickname = nickname;
}
void Client::setUsername(const std::string& username){
	this->_username = username;
}
void Client::setStatus(int status){
	this->status = status;
}
void Client::setClientFd(int client_fd){
	this->_client_fd = client_fd;
}
void Client::setChannelName(const std::string& channel_name){
	this->channel_name = channel_name;
}