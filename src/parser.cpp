/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:12:07 by theog             #+#    #+#             */
/*   Updated: 2025/11/20 18:01:28 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

bool is_cmd(std::string str)
{
	if (is_first_wrd_capital(str) == false)
		return (false);
    for(int i = 0; i < 1; i++)
    {
        if (startsWith(str, "PASS") == true)
            return(true);
        if (startsWith(str, "NICK") == true)
            return(true);
        if (startsWith(str, "USER") == true)
            return(true);
        if (startsWith(str, "JOIN") == true)
            return(true);
        if (startsWith(str, "LEAVE") == true)
            return(true);
        if (startsWith(str, "PRIVMSG") == true)
            return(true);
    }
    return(false);
}

std::string trim_cmd(std::string str)
{
	return (remove_1st_word(str));
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
    std::string input_name = trim_cmd(cmd);
	std::string channel_name = "#";
	channel_name += input_name;
    int i = get_channel_index(channel_name, channels);
	std::vector<std::string> channel_list = client->get_channel_list();
	if (is_inside(channel_list, channel_name) == true)
		return;
    if (i != -1)
    {
        channels[i]->addClient(client);
		channel_list.push_back(channel_name);
        client->setChannelName(channel_name);
        client->setStatus(IN_CHANNEL);
        std::cout << client->getUsername() << " has joined " << channel_name << std::endl;
    }
    else
    {
        Channel *new_channel = new Channel(channel_name);
        channels.push_back(new_channel);
        new_channel->addClient(client);
		channel_list.push_back(channel_name);
        client->setChannelName(new_channel->getName());
        client->setStatus(IN_CHANNEL);
        std::cout << "Channel " << channel_name << " created\n";
    }
}

//channel list upadte keep going from here

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
		client->remove_channel_fromchannelList(channel_name);
        if (channels[i]->getNbClient() <= 0)
            channels.erase(channels.begin() + i);
        std::cout << client->getUsername() << " has left " << channel_name << std::endl;
    }
}

void pass(std::string cmd, Client *client, Server* server)
{
	std::vector<std::string> tab = ft_split(cmd, ' ');
	if (tab.size() < 2)
	{
		server->sendRPL(client, 461, "PASS :Not enough parameters");
		return;
	}
    std::string input = remove_1st_word(cmd);

	if (client->getStatus() == CONNECTED)
	{
		server->sendRPL(client, 462, "Error, already registered");
		return;
	}
	if (client->getStatus() == WAITING_PASSWORD) {
		if (server->check_password(input)) {
			client->setStatus(WAITING_NICKNAME);
			server->sendMessage(client->getClientFd(), "Password OK. Please type nickname:\n");
		} else {
			server->sendRPL(client, 464, ":Password incorrect");
			server->closeClient(client->getClientFd());
		}
	}
}

void username(std::string cmd, Client *client, Server *server)
{
	std::string username = trim_cmd(cmd);
	std::vector<std::string> user_list = server->get_user_list();
	if(client->getStatus() == WAITING_USERNAME)
	{
		client->setUsername(username);
		client->setStatus(CONNECTED);
		user_list.push_back(username);
		server->sendMessage(client->getClientFd(), "Please type nickname\n");
	}
}

void nickname(std::string cmd, Client *client, Server *server)
{
	std::vector<std::string> tab = ft_split(cmd, ' ');
	if (tab.size() < 2)
	{
		server->sendRPL(client, 431, ":No nickname given");
		return;
	}
	std::string nick = trim_cmd(cmd);
	if (check_valid_nickname(nick) == false)
	{
		std::string rpl = nick + " :Erroneous nickname";
		server->sendRPL(client, 432, rpl);
		return;
	}
	std::vector<std::string> nickname_list = server->get_nickname_list();
	if (is_inside(nickname_list, nick))
	{
		std::string rpl = nick + " :Nickname is already in use";
		server->sendRPL(client, 433, rpl);
		return;
	}
	if(client->getStatus() == WAITING_NICKNAME)
	{
		client->setNickname(nick);
		nickname_list.push_back(nick);
		client->setStatus(WAITING_USERNAME);
		server->sendMessage(client->getClientFd(), "Welcome to server\n");
	}
}

void privmsg(std::string cmd, Client *client, Server *server)
{
	std::vector<std::string> input = ft_split(cmd, ' ');
	std::string reply;
	std::string msg = remove_1st_word(cmd);
	msg = remove_1st_word(msg);
	msg += "\n";

	if (input.size() < 3)
	{
		reply = format_client_reply(client, 411, ":No recipient or text provided");
		server->sendMessage(client->getClientFd(), reply);
		return;
	}
	if (input[1][0] == '#')
	{
		Channel *channel = server->get_channel_by_name(input[1]);
		if (!channel)
		{
			std::cout << "Channel does not exist" << std::endl;
			return;
		}
		if (!(is_inside(client->get_channel_list(), input[1])))
		{
			std::cout << "Client is not part of channel " << input[1] << std::endl;
		}
		channel->sendMessageToAllClients(msg, client);
	}
	else
	{
		Client *dest = server->get_client_by_nick(input[1]);
		if (!dest)
			return;
		client->sendMessage(dest->getClientFd(), msg);
	}
}

void make_command(std::string cmd, Client *client, Server* server)
{
	if (startsWith(cmd, "JOIN"))
		join(cmd, client, server->get_channels());
	if (startsWith(cmd, "LEAVE"))
		leave(client, server->get_channels());
	if (startsWith(cmd, "PASS"))
		pass(cmd, client, server);
	if (startsWith(cmd, "NICK"))
		nickname(cmd, client, server);
	if (startsWith(cmd, "USER"))
		username(cmd, client, server);
	if (startsWith(cmd, "PRIVMSG"))
		privmsg(cmd, client, server);
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