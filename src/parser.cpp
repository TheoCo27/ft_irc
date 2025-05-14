/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:12:07 by theog             #+#    #+#             */
/*   Updated: 2025/05/14 04:19:00 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"
#include "../includes/server.hpp"



bool startsWith(const std::string& input, const std::string& prefix) {
    if (input.size() < prefix.size())
        return false;
    return input.compare(0, prefix.size(), prefix) == 0;
}


bool is_cmd(std::string str)
{
    std::string tab_cmd[1];

    tab_cmd[0] = "/join";

    for(int i = 0; i < 1; i++)
    {
        if (startsWith(str, tab_cmd[i]) == true)
            return(true);
    }
    return(false);
}

int get_cmd_index()

void make_command(std::string cmd, Client *client, std::vector<Client*> client_tab, std::vector<Channel*> channels)
{
    
}