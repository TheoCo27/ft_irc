/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:12:07 by theog             #+#    #+#             */
/*   Updated: 2025/05/15 18:36:45 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"



bool startsWith(const std::string& input, const std::string& prefix) {
    if (input.size() < prefix.size())
        return false;
    return input.compare(0, prefix.size(), prefix) == 0;
}


bool is_cmd(std::string str)
{

    for(int i = 0; i < 1; i++)
    {
        if (startsWith(str, "/join") == true)
            return(true);
        if (startsWith(str, "/leave") == true)
            return(true);
    }
    return(false);
}

std::string trim_cmd(std::string str)
{
    int i = 0;
    while(str[i] && str[i] != ' ')
        i++;
    while(str[i] && str[i] == ' ')
        i++;
    str.erase(0, i);
    str.erase(str.length() - 1, 1);
    return (str);
}

int get_channel_index(std::string name, std::vector<Channel*> channels)
{
	for (size_t i = 0; i < channels.size(); ++i) 
	{
        if (channels[i] && channels[i]->getName() == name) {
            return static_cast<int>(i);
        }
    }
    return (-1); // pas trouvé
}

void join(std::string cmd, Client *client, std::vector<Channel*>& channels)
{
    std::cout << "inside join\n";
    std::string channel_name = trim_cmd(cmd);
    int i = get_channel_index(channel_name, channels);
    if (i != -1)
    {
        channels[i]->addClient(client);
        client->setChannelName(channel_name);
        client->setStatus(IN_CHANNEL);
        std::cout << client->getUsername() << " has joined " << channel_name << std::endl;
    }
    else
    {
        Channel *new_channel = new Channel(channel_name);
        channels.push_back(new_channel);
        new_channel->addClient(client);
        client->setChannelName(channel_name);
        client->setStatus(IN_CHANNEL);
        std::cout << "Channel " << channel_name << " created\n";
    }
}

void leave(Client *client, std::vector<Channel*>& channels)
{
    if (client->getStatus() == CONNECTED)
        return;
    std::string channel_name = client->getChannelName();
    int i = get_channel_index(channel_name, channels);
    if (i != -1)
    {
        channels[i]->removeClient(client);
        client->setChannelName("");;
        client->setStatus(CONNECTED);
        if (channels[i]->getNbClient() <= 0)
            channels.erase(channels.begin() + i);
        std::cout << client->getUsername() << " has left " << channel_name << std::endl;
    }
}

void make_command(std::string cmd, Client *client, std::vector<Client*>& client_tab, std::vector<Channel*>& channels)
{
    std::cout << "inside Make_command\n";
    if (startsWith(cmd, "/join"))
        join(cmd, client, channels);
    if (startsWith(cmd, "/leave"))
        leave(client, channels);
    (void)client_tab;
}