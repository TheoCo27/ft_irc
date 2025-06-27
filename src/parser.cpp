/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:12:07 by theog             #+#    #+#             */
/*   Updated: 2025/06/28 00:08:09 by theog            ###   ########.fr       */
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
        if (startsWith(str, "PASS") == true)
            return(true);
        if (startsWith(str, "NICK") == true)
            return(true);
        if (startsWith(str, "USER") == true)
            return(true);
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

void pass(std::string cmd, Client *client, Server* server)
{
    std::string input(cmd);

	if (client->getStatus() == WAITING_PASSWORD) {
		if (server->check_password(input)) {
			client->setStatus(WAITING_NICKNAME);
			server->sendMessage(client->getClientFd(), "Password OK. Please type nickname:\n");
		} else {
			server->sendMessage(client->getClientFd(), "Wrong password. Connection closed.\n");
			server->closeClient(client->getClientFd());
			server->removeClient(client->getClientFd());
		}
	}
}

void make_command(std::string cmd, Client *client, Server* server)
{
    std::cout << "inside Make_command\n";
    if (startsWith(cmd, "/join"))
        join(cmd, client, server->get_channels());
    if (startsWith(cmd, "/leave"))
        leave(client, server->get_channels());
    if (startsWith(cmd, "PASS"))
        pass(cmd, client, server);
}

	// if (client->getStatus() == WAITING_PASSWORD) {
	// 	if (check_password(input)) {
	// 		client->setStatus(WAITING_USERNAME);
	// 		sendMessage(client_fd, "Password OK. Please type username:\n");
	// 	} else {
	// 		sendMessage(client_fd, "Wrong password. Connection closed.\n");
	// 		closeClient(client_fd);
	// 		removeClient(client_fd);
	// 	}
	// }
	// else if (client->getStatus() == WAITING_USERNAME) {
	// 	client->setUsername(input);
	// 	client->setStatus(CONNECTED);
	// 	sendMessage(client_fd, "Welcome to the server!\n");
	// 	std::cout << "🟢 Client connecté (fd: " << client_fd << ")" << std::endl;
	// }