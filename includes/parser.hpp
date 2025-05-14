/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:19:26 by theog             #+#    #+#             */
/*   Updated: 2025/05/14 16:20:53 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "server.hpp"
#include <string>

bool is_cmd(std::string str);
void make_command(std::string cmd, Client *client, std::vector<Client*>& client_tab, std::vector<Channel*>& channels);