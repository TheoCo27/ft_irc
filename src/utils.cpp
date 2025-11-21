/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:09:42 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/21 19:20:26 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

bool startsWith(const std::string& input, const std::string& prefix) {
    if (input.size() < prefix.size())
        return false;
    return input.compare(0, prefix.size(), prefix) == 0;
}

void decapitalize(std::string &str) 
{
	if (str.empty())
		return;
	for(int i = 0; str[i]; i++)
	{
		if (std::isupper(static_cast<unsigned char>(str[i])))
			str[i] = std::tolower(static_cast<unsigned char>(str[i]));
	}
}

std::string remove_1st_word(std::string str)
{
	size_t i = 0;
	while(str[i] && std::isspace(static_cast<unsigned char>(str[i])))
		i++;
	while(str[i] && !(std::isspace(static_cast<unsigned char>(str[i]))))
		i++;
	while(str[i] && std::isspace(static_cast<unsigned char>(str[i])))
		i++;
	if (i < str.size())
		return str.substr(i);
	return "";
}

bool is_inside(std::vector<std::string> vec, std::string to_find)
{
	std::vector<std::string>::iterator it = std::find(vec.begin(), vec.end(), to_find);
	if(it != vec.end())
		return true;
	else
		return false;
}

void remove_from_vec(std::vector<std::string>& vec, std::string to_remove)
{
	std::vector<std::string>::iterator it = std::find(vec.begin(), vec.end(), to_remove);
		if(it != vec.end())
			vec.erase(it);
		else
			return;	
}

bool is_first_wrd_capital(std::string str)
{
	for(size_t i = 0; i < str.size(); i++)
	{
		if (!(std::isupper(static_cast<unsigned char>(str[i]))) && !(std::isspace(static_cast<unsigned char>(str[i]))))
			return (std::cout << "im out\n", 0);
		if (std::isspace(static_cast<unsigned char>(str[i])))
			break;
	}
	return 1;
}

std::string format_client_notice(Client* client, const std::string& msg)
{
    std::stringstream ss;
    ss << ":server.42irc NOTICE " << client->getNickname() << " :" << msg << "\r\n";
    return ss.str();
}

std::string format_client_reply(Client *client, int rpl_code, std::string msg)
{
	std::string reply;
	std::stringstream ss;

	ss << ":server.42irc " << rpl_code << " " << client->getNickname() << " " << msg << "\r\n";
	reply = ss.str();
	return (reply);
}

std::vector<std::string> ft_split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
        result.push_back(item);

    return result;
}

static bool is_valid_char_for_nickname(char c)
{
	char set[] = "-[]{}|`^\\";
	
	if (!(std::isprint(static_cast<int>(c))))
		return false;
	if (std::isalpha(static_cast<int>(c)) || std::isdigit(static_cast<int>(c)))
		return true;
	for(int i = 0; set[i]; i++)
		if (c == set[i])
			return true;
	return false;
}

bool check_valid_nickname(std::string nick)
{
	if (nick.empty())
		return false;
	if(nick.length() > 9)
		return false;
	if (std::isalpha(static_cast<int>(nick[0])) == false)
		return false;
	for(size_t i = 0; nick[i]; i++)
		if(is_valid_char_for_nickname(nick[i]) == false)
			return false;
	return true;
}

static bool is_valid_char_for_username(char c)
{
	char set[] = ". _ - ~";
	
	if (!(std::isprint(static_cast<int>(c))))
		return false;
	if (std::isalpha(static_cast<int>(c)) || std::isdigit(static_cast<int>(c)))
		return true;
	for(int i = 0; set[i]; i++)
		if (c == set[i])
			return true;
	return false;
}

bool check_valid_username(std::string user)
{
	if (user.empty())
		return false;
	if(user.length() > 10)
		return false;
	for(size_t i = 0; user[i]; i++)
		if(is_valid_char_for_username(user[i]) == false)
			return false;
	return true;
}

bool check_valid_realname(std::string rname)
{
	std::string output(rname);

	if(output.length() > 50)
		return false;
	for(size_t i = 0; output[i]; i++)
		if(!(std::isprint(static_cast<int>(rname[i]))))
			return false;
	return true;
}

std::string trunc(const std::string& str, size_t len_to_trunc)
{
    if (str.size() <= len_to_trunc)
        return str;
    return str.substr(0, len_to_trunc);
}

std::string get_valid_username(std::string user)
{
	std::string output(user);

	if(user.length() > 10)
		output = trunc(user, 10);
	for(size_t i = 0; output[i]; i++)
		if(is_valid_char_for_username(output[i]) == false)
			output[i] = 'o';
	return output;
}

std::string get_valid_realname(std::string rname)
{
	std::string output(rname);

	if(output.length() > 50)
		output = trunc(rname, 50);
	if (output[0] == ':')
		output.erase(0, 1);
	for(size_t i = 0; output[i]; i++)
		if(!(std::isprint(static_cast<int>(rname[i]))))
			output[i] = 'o';
	return output;
}

int remove_flag(int status, int flag_to_remove)
{
	status &= ~flag_to_remove;
	return status;
}
