/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:44:49 by theog             #+#    #+#             */
/*   Updated: 2025/11/29 17:05:44 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

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
	if(nick == "bot")
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
	char set[] = "._-~";
	
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

// std::string get_valid_username(std::string user)
// {
// 	std::string output(user);

// 	for(size_t i = 0; output[i]; i++)
// 		if(is_valid_char_for_username(output[i]) == false)
// 			output[i] = 'o';
// 	if(user.length() > 10)
// 		output = trunc(user, 10);
// 	return output;
// }

std::string get_valid_username(std::string user)
{
    std::string output;

    std::string tmp = user;
    if (tmp.size() > 10)
        tmp = tmp.substr(0, 10);

    for (size_t i = 0; i < tmp.size(); i++)
    {
        if (is_valid_char_for_username(tmp[i]))
            output += tmp[i];
    }

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
		if(!(std::isprint(static_cast<int>(rname[i]))) || output[i] == '\r' || output[i] == '\n')
			output[i] = 'o';
	return output;
}

bool check_valid_channel_name(std::string name)
{
	if (name.empty() || name.length() > 50)
		return (false);
	if (name[0] != '#' && name[0] != '&')
		return (false);
	for(size_t i = 0; name[i]; i++)
	{
		if(std::isspace(static_cast<int>(name[i])) || name[i] == ',' || (!(std::isprint(static_cast<int>(name[i])))))
			return false;
		if (name[i] == '\r' || name[i] == '\n')
        	return false;
	}
	return true;
}

bool is_valid_mode(std::string mode)
{
	if(mode.length() != 2)
		return false;
	if(mode[0] != '+' && mode[0] != '-')
		return false;
	if(mode[1] != 'i' && mode[1] != 't' && mode[1] != 'k' && mode[1] != 'l' && mode[1] != 'o')
		return false;
	return true;
}


std::string is_valid_topic(std::string topic)
{
	std::string output(topic);

	if(output.length() > 307)
		trunc(topic, 307);
	for(size_t i = 0; output[i]; i++)
	{
		if(!(std::isprint(static_cast<int>(output[i]))))
			return "";
		if (output[i] == '\r' || output[i] == '\n')
        	return "";
	}
	return output;
}

std::string get_valid_privmsg(std::string input)
{
	std::string msg(input);
	if(msg.length() > 512)
		trunc(msg, 512);
	return msg;
}