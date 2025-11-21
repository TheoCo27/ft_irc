/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:06 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/21 13:45:57 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client(int client_fd)
{
	this->_client_fd = client_fd;
	this->_nickname = "*";
	this->_username = "*";
	this->_realname = "realname.com";
	this->status = EMPTY;
	this->channel_name = "";
	this->old_buf = "";
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

void Client::remove_channel_fromchannelList(std::string channel_name)
{
	std::vector<std::string>::iterator it = std::find(this->channel_list.begin(), this->channel_list.end(), channel_name);
	if (it != this->channel_list.end()) {
		this->channel_list.erase(it);
	}
}
std::string Client::format_RPL(std::string msg)
{
	std::string reply = ":" + this->_nickname + "!" + this->_username + "@" + this->_realname + msg;
	return reply;
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

std::string& Client::getold_buf()
{
	return this->old_buf;
}

std::vector<std::string> &Client::get_channel_list()
{
	return this->channel_list;
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

void Client::setOld_buf(std::string new_buf){
	this->old_buf = new_buf;
}
