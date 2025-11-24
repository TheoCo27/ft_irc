/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:12:07 by theog             #+#    #+#             */
/*   Updated: 2025/11/24 19:44:32 by tcohen           ###   ########.fr       */
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

void send_join_success_rpl(Channel *channel, Client *client, Server *server)
{
	//prevenir les users
	std::string msg;
	msg = client->format_RPL(" JOIN " + channel->getName());
	channel->sendMessageToAllClients(msg, NULL);
	server->sendRPL(client, 332, channel->getName() + " :" + channel->get_topic());
	server->sendRPL(client, 353, "= " + channel->getName() + " :" + channel->get_client_list());
	server->sendRPL(client, 366, channel->getName() + " :End of /NAMES list");

}

void join(std::string cmd, Client *client, Server *server)
{
	std::vector<Channel*>& channels = server->get_channels();
	std::vector<std::string> input = ft_split(cmd, ' ');
	std::vector<std::string>& channel_list = client->get_channel_list();

	if (input.size() < 2)
		return(server->sendRPL(client, 461, "JOIN :Not enough parameters"));
	if (!input[1].empty() && input[1] == "0")
	{
		//part from all channels
		return;
	}
	if (check_valid_channel_name(input[1]) == false)
		return(server->sendRPL(client, 476, input[1] + " :Bad Channel Mask"));
	if(is_inside(client->get_channel_list(), input[1]))
		return;
	if(channel_list.size() >= 10)
		return(server->sendRPL(client, 405, input[1] + " :You have joined too many channels"));
	
    int i = get_channel_index(input[1], channels);
    if (i != -1)
    {
		if(channels[i]->is_invite_only() == 1 && is_inside(channels[i]->get_invited_nick(), client->getNickname()) == false)
			return(server->sendRPL(client, 473, input[1] + " :Cannot join channel (+i)"));
		if (channels[i]->check_has_password() == 1)
			if (input.size() < 3 || input[2] != channels[i]->get_pass())
				return(server->sendRPL(client, 475, input[1] + " :Cannot join channel (+k)"));
		if(channels[i]->check_has_limit_user() == true && channels[i]->getNbClient() == channels[i]->get_limit_user())
			return(server->sendRPL(client, 471, input[1] + ":Cannot join channel (+l)"));
        channels[i]->addClient(client); // ajoute le client au channel
		channel_list.push_back(input[1]); //ajoute le channel a la liste client
        //client->setChannelName(input[1]);
        //client->setStatus(IN_CHANNEL);
        std::cout << client->getNickname() << " has joined " << input[1] << std::endl;
		send_join_success_rpl(channels[i], client, server);
    }
    else
    {
        Channel *new_channel = new Channel(input[1]);
		std::vector<Client *>& new_channel_op_lst = new_channel->get_operators();
        channels.push_back(new_channel); // ajoute le channel a la liste server
        new_channel->addClient(client); // ajoute le client a la liste du channel
		channel_list.push_back(input[1]); // ajoute le channel a la liste du client
		new_channel_op_lst.push_back(client); // ajoute le client a la liste des op du channel
        //client->setChannelName(new_channel->getName());
        //client->setStatus(IN_CHANNEL);
        std::cout << "Channel " << input[1] << " created\n";
		send_join_success_rpl(new_channel, client, server);
    }
}

//channel list upadte keep going from here

void leave(Client *client, std::vector<Channel*>& channels)
{
    if (client->getStatus() & CONNECTED)
        return;
    std::string channel_name = client->getChannelName();
    int i = get_channel_index(channel_name, channels);
    if (i != -1)
    {
        channels[i]->removeClient(client);
        client->setChannelName("");;
        client->setStatus(client->getStatus() | CONNECTED);
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

	if (client->getStatus() & CONNECTED)
	{
		server->sendRPL(client, 462, "Error, already registered");
		return;
	}
	if (client->getStatus() == EMPTY) {
		if (server->check_password(input)) {
			client->setStatus(PASSWORD_OK);
			//server->sendNotice(client, "Password OK. Please type nickname:");
		} else {
			server->sendRPL(client, 464, ":Password incorrect");
			server->closeClient(client->getClientFd());
		}
	}
}
std::string get_realname(std::string cmd)
{	
	std::string realname(cmd);
	for(int i = 0; i < 4; i++)
		realname = remove_1st_word(realname);
	return realname;
}

void connect_client(Client *client, Server *server)
{
	std::cout << "inside connect client\n";
	if ((client->getStatus() & (PASSWORD_OK | NICK_OK | USER_OK)) == (PASSWORD_OK | NICK_OK | USER_OK))
	{
		client->setStatus(client->getStatus() | CONNECTED);
		server->sendRPL(client, 001, "Welcome to the IRC network, " + client->getNickname() + "!" + client->getUsername() + "@" + client->getRealname());
		server->sendRPL(client, 002, "Your host is server.42irc, running version 1.0");
		server->sendRPL(client, 003, "This server was created on 2025/11/07 00:04:20");
		server->sendRPL(client, 004,  "server.42irc 1.0 o o");
	}
}
void username(std::string cmd, Client *client, Server *server)
{
	std::cout << "inside user cmd\n";
	std::vector<std::string> parsed_input = ft_split(cmd, ' ');

	if (parsed_input.size() < 5)
	{
		server->sendRPL(client, 461, "USER :Not enough parameters");
		return;
	}
	if (client->getStatus() & CONNECTED || !(client->getStatus() & PASSWORD_OK))
	{
		if (client->getStatus() & CONNECTED)
		server->sendRPL(client, 462, "You may not reregister");
		if (!(client->getStatus() & CONNECTED))
			server->sendNotice(client, "Use PASS command first");
		return;
	}
	std::string username = parsed_input[1];
	if (check_valid_username(username) == false)
	{
		username = get_valid_username(username);
		server->sendNotice(client, "Invalid username has been normalized");

	}
	std::string mode = parsed_input[2];
	std::string realname = get_realname(cmd);
	if (check_valid_realname(realname) == false)
		server->sendNotice(client, "Invalid realname has been normalized");
	realname = get_valid_realname(realname);
	client->setUsername(username);
	client->setRealname(realname);
	client->setStatus(client->getStatus() | USER_OK);
	connect_client(client, server);
}

void nickname(std::string cmd, Client *client, Server *server)
{
	if (!(client->getStatus() & PASSWORD_OK))
	{
		server->sendRPL(client, 462, "You may not reregister");
		server->sendNotice(client, "Use PASS command first");
		return;
	}
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
	if(client->getStatus() & PASSWORD_OK && (!(client->getStatus() & CONNECTED)))
	{
		client->setNickname(nick);
		nickname_list.push_back(nick);
		client->setStatus(client->getStatus() | NICK_OK);
		connect_client(client, server);
	}
	else if(client->getStatus() & CONNECTED || client->getStatus() & IN_CHANNEL)
	{
		std::vector<std::string> channel_list = client->get_channel_list();
		std::string msg = " NICK:" + nick + "\r\n";
		msg = client->format_RPL(nick);
		for(size_t i = 0; i < channel_list.size(); i++)
		{
			Channel* channel = server->get_channel_by_name(channel_list[i]);
			channel->sendMessageToAllClients(msg, client);
		}
		remove_from_vec(nickname_list, client->getNickname());
		client->setNickname(nick);
		nickname_list.push_back(nick);
		server->sendMessage(client->getClientFd(), msg);
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

std::string get_channel_pass(std::string cmd)
{	
	std::string channel_pass(cmd);
	for(int i = 0; i < 3; i++)
		channel_pass = remove_1st_word(channel_pass);
	return channel_pass;
}

void mode(std::string cmd, Client *client, Server* server)
{
	//gerer MODE #chan -> truc speciale a envoyer
	//gerer MODE +xyz -> unknown mode

	std::vector<std::string> input = ft_split(cmd, ' ');
	if(input.size() <= 1)
		return(server->sendRPL(client, 461, "MODE :Not enough parameters"));	
	Channel *channel = server->get_channel_by_name(input[1]);
	std::string password;
	if (!channel)
		return(server->sendRPL(client, 403, channel->getName() + " :No such channel"));
	if (!channel->is_op(client))
		return(server->sendRPL(client, 482, channel->getName() + " :You're not channel operator"));
	if (!channel->is_client(client))
		return(server->sendRPL(client, 442, channel->getName() + " :You're not on that channel"));
	if(input.size() > 2 && (input[2] == "+k" || input[2] == "+l" || input[2] == "+o" || input[2] == "-o") && input.size() < 4)
		return(server->sendRPL(client, 461, "MODE :Not enough parameters"));
	if((input[2] == "+o" || input[2] == "-o") && !(channel->is_client(server->get_client_by_nick(input[3])))  )
		return(server->sendRPL(client, 441, input[3] + " " + channel->getName() + " :User not in channel"));
	//error management on top mode controle down here
	if (input[2] == "+i")
		channel->set_invite_only(true);
	if (input[2] == "-i")
		channel->set_invite_only(false);
	if(input[2] == "+t")
		channel->set_topic_restricted(true);
	if(input[2] == "-t")
		channel->set_topic_restricted(false);
	if(input[2] == "-k")
		channel->set_has_password(false);
	if(input[2] == "+k")
	{
		channel->set_has_password(true);
		channel->set_pass(get_channel_pass(cmd));
	}
	if(input[2] == "-l")
		channel->set_has_limit_user(false);
	if (input[2] == "+l")
	{
		channel->set_has_limit_user(true);
		if (ft_sto_ui(input[3]) <= 0)
			return(server->sendNotice(client, "MODE (+l): invalid limit"));
		channel->set_limit_user(std::atoi(input[3].c_str()));
	}
	if(input[2] == "+o" || input[2] == "-o")
	{
		Client *new_op = server->get_client_by_nick(input[3]);
		if(input[2] == "+o")
			channel->get_operators().push_back(new_op);
		if(input[2] == "-o")
			channel->remove_op(new_op);
	}
	std::string msg;
	int i = 0;
	while(i < input.size())
	{
		if(i != 0)
			msg += " ";
		msg += input[i];
		i++;
		if ((input[2] == "+i" || input[2] == "-i" || input[2] == "+t" || input[2] == "-t" || input[2] == "-k" || input[2] == "+k"|| input[2] == "-l") && i > 2)
			break;
		if ((input[2] == "+l" || input[2] == "-o" || input[2] == "+o") && i > 3)
			break;
	}
	if (input[2] == "-k" || input[i] == "+k")
		msg = msg + " " + channel->get_pass();
	msg = client->format_RPL(msg);
	channel->sendMessageToAllClients(msg, NULL);
}

void make_command(std::string cmd, Client *client, Server* server)
{
	if (startsWith(cmd, "JOIN"))
		join(cmd, client, server);
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