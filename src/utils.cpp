/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:09:42 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/03 18:34:01 by tcohen           ###   ########.fr       */
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
    int i = 0;
    while(str[i] && !(std::isspace(static_cast<unsigned char>(str[i]))))
        i++;
    while(str[i] && std::isspace(static_cast<unsigned char>(str[i])))
        i++;
    str.erase(0, i);
    str.erase(str.length() - 1, 1);
    return (str);
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