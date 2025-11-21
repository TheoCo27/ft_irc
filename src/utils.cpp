/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:09:42 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/21 14:24:34 by theog            ###   ########.fr       */
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

std::string format_client_reply(Client *client, int rpl_code, std::string msg)
{
	std::string reply;
	std::stringstream ss;

	ss << ":server " << rpl_code << " " << client->getNickname() << " " << msg << "\r\n";
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
	if (std::isalpha(static_cast<int>(nick[0])) == false)
		return false;
	for(size_t i = 0; nick[i]; i++)
		if(is_valid_char_for_nickname(nick[i]) == false)
			return false;
	return true;
}

int remove_flag(int status, int flag_to_remove)
{
	status &= ~flag_to_remove;
	return status;
}
