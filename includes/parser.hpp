/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 02:19:26 by theog             #+#    #+#             */
/*   Updated: 2025/10/25 16:18:48 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "server.hpp"
#include "utils.hpp"
#include <string>

class Server;

bool is_cmd(std::string str);
void make_command(std::string cmd, Client *client, Server* server);