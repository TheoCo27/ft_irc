/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:00 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/03 14:15:26 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channel.hpp"

Channel::Channel(std::string name)
{
	if(startsWith(name, "#") == true)
		this->name = name;
	else
	{
		std::string new_name = "#" + name;
		this->name = new_name;
	}
	nb_client = 0;
}

Channel::~Channel()
{
}


void Channel::addClient(Client* client)
{
    nb_client++;
    std::string welcome = "Welcome to ";
    welcome.append(this->name);
    welcome.append(" channel\n");
    sendMessage(client->getClientFd(), welcome);
    std::string joined = client->getUsername() + " has joined channel\n";
    sendMessageToAllClients(joined, client);
	clients.push_back(client);
}

int Channel::get_client_index(Client *client)
{
    std::vector<Client*>::iterator it = std::find(clients.begin(), clients.end(), client);
    if (it != clients.end()) {
        return (it - clients.begin());
    } 
    else
        return (-1);
}
void Channel::removeClient(Client* client)
{
    int index = get_client_index(client);
    if (index == -1)
        return;
    clients.erase(clients.begin() + index);
    nb_client--;
    std:: string left = client->getUsername() + " has left channel\n";
    sendMessageToAllClients(left, NULL);
}

void Channel::sendMessageToAllClients(const std::string& message, Client *client)
{
    std::string from;
    if (client != NULL)
    {
        from = "From ";
        from.append(client->getUsername());
        from.append(": ");
        from.append(message);
    }
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* ptr = *it;
        if (client != NULL && client != ptr)
            send(ptr->getClientFd(), from.c_str(), from.size(), 0);
        else if(client == NULL)
            send(ptr->getClientFd(), message.c_str(), message.size(), 0);
    }
}

void Channel::sendMessage(int client_fd, const std::string& message)
{
	send(client_fd, message.c_str(), message.size(), 0);
}

std::string Channel::receiveMessage(int client_fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return "";
	buffer[bytes] = '\0';
	return std::string(buffer);
}
//getters
std::string Channel::getName() const{ return (name);}
int Channel::getNbClient() const{return (nb_client);}
//settters
void Channel::setName(const std::string& name){this->name = name;}
void Channel::setNbClient(int nb_client){this->nb_client = nb_client;}