/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:00 by tcohen            #+#    #+#             */
/*   Updated: 2025/12/03 18:35:48 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channel.hpp"
#include "../includes/utils.hpp"

Channel::Channel(std::string name)
{
    this->name = name;
    topic = "No topic set";
	nb_client = 0;
    topic_restricted = 0;
    has_password = 0;
    has_limit_user = 0;
    invite_only = 0;
    limit_user = -1;
    creation_time = std::time(NULL);
}

Channel::~Channel()
{
	clients.clear();     // ne delete pas les clients, juste enlève les pointeurs
    operators.clear();
}


void Channel::addClient(Client* client)
{
    nb_client++;
    // std::string welcome = "Welcome to ";
    // welcome.append(this->name);
    // welcome.append(" channel\n");
    // sendMessage(client->getClientFd(), welcome);
    // std::string joined = client->getUsername() + " has joined channel\n";
    // sendMessageToAllClients(joined, client);
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

// static int get_operators_index(Client *client, std::vector<Client*> op_list)
// {
//     std::vector<Client*>::iterator it = std::find(op_list.begin(), op_list.end(), client);
//     if (it != op_list.end()) {
//         return (it - op_list.begin());
//     } 
//     else
//         return (-1);
// }
void Channel::removeClient(Client* client)
{
    //need to update with operators management
    int index = get_client_index(client);
    if (index == -1)
        return;
    clients.erase(clients.begin() + index);
    nb_client--;
    // std:: string left = client->getUsername() + " has left channel\n";
    // sendMessageToAllClients(left, NULL);
}

void Channel::sendMessageToAllClients(const std::string& message, Client *client)
{
    std::string from(message);
    // if (client != NULL)
    // {
    //     from = "From ";
    //     from.append(client->getUsername());
    //     from.append(": ");
    //     from.append(message);
    // }
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* ptr = *it;
        if (client != NULL && client != ptr)
            send(ptr->getClientFd(), message.c_str(), message.size(), 0);
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

		std::vector<Client*> voiced;
bool Channel::is_op(Client *client)
{
    for (std::vector<Client*>::iterator it = operators.begin(); it != operators.end(); ++it)
    {
        if (*it == client)
            return true;
    }
    return false;
}


// bool Channel::is_voiced(Client *client)
// {
//     for (std::vector<Client*>::iterator it = voiced.begin(); it != voiced.end(); ++it)
//     {
//         if (*it == client)
//             return true;
//     }
//     return false;
// }

bool Channel::is_client(Client *client)
{
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (*it == client)
            return true;
    }
    return false;
}


std::string Channel::get_client_list()
{
    std::string list = "";

    for(std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if(list != "")
            list += " ";
        Client* client = *it;
        if(is_op(client) == true)
            list += "@";
        list += client->getNickname();
    }
	std::cout << "client list for channel " << this->name << " is : " << list << std::endl;
    return list;
}

void Channel::remove_op(Client *client)
{
	std::vector<Client*>::iterator it = operators.begin();

    for (; it != operators.end(); ++it)
    {
        if (*it == client)
        {
            operators.erase(it);
            return;
        }
    }
}


std::string Channel::get_mode_list()
{
	std::stringstream ss(this->name);

	if(invite_only || topic_restricted || has_password || has_limit_user)
		ss << " +";
	if(invite_only)
		ss << "i";
	if(topic_restricted)
		ss << "t";
	if(has_password)
		ss << "k";
	if(has_limit_user)
		ss << "l";
	if(has_password)
		ss << " " << this->password;
	if(has_limit_user)
		ss << " " << this->limit_user;
	return (ss.str());
}



//getters
std::string Channel::getName() const{ return (name);}
int Channel::getNbClient() const{return (nb_client);}
//
std::string Channel::get_pass(){ return(password);}
std::string Channel::get_topic(){return(topic);}
std::vector<Client *>& Channel::get_operators(){return(operators);}
std::vector<std::string>& Channel::get_invited_nick(){return(invited_nick);}
bool Channel::is_topic_restricted(){return(topic_restricted);}
bool Channel::check_has_password(){return(has_password);}
bool Channel::check_has_limit_user(){return(has_limit_user);}
bool Channel::is_invite_only(){return(invite_only);}
int Channel::get_limit_user(){return(limit_user);}
std::time_t Channel::get_creation_time(){return(creation_time);}

//settters
void Channel::setName(const std::string& name){this->name = name;}
void Channel::setNbClient(int nb_client){this->nb_client = nb_client;}
//
void Channel::set_pass(std::string pass){this->password = pass;}
void Channel::set_topic(std::string topic){this->topic = topic;}
void Channel::set_topic_restricted(bool is_restricted){this->topic_restricted = is_restricted;}
void Channel::set_has_password(bool has_pass){this->has_password = has_pass;}
void Channel::set_has_limit_user(bool has_limit_user){this->has_limit_user = has_limit_user;}
void Channel::set_invite_only(bool is_invite_only){this->invite_only = is_invite_only;}
void Channel::set_limit_user(int limit_user){this->limit_user = limit_user;}
void Channel::add_op(Client* client){

	if(is_op(client))
		return;
	operators.push_back(client);
}