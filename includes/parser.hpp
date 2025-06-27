/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:19:26 by theog             #+#    #+#             */
/*   Updated: 2025/06/13 15:57:08 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "server.hpp"
#include <string>

bool is_cmd(std::string str);
void make_command(std::string cmd, Client *client, Server* server);