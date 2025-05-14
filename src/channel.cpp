/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:00 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 03:13:14 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channel.hpp"

Channel::Channel(std::string name) : name(name), nb_client(0)
{
}

Channel::~Channel()
{
}


void Channel::addClient(Client* client)
{
    nb_client++;
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
}

void Channel::sendMessageToAllClients(const std::string& message)
{
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* ptr = *it;
        send(ptr->_client_fd, message.c_str(), message.size(), 0);
    }
}
std::string Channel::getName() const{ return (name);}
std::vector<Client*> Channel::getClients() const{return (clients);}