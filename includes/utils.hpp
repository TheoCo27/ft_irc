/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:15:22 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/27 02:57:36 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
// #include "client.hpp"
// #include "server.hpp"
#include <sstream>
#include <ctime>

class Server;
class Client;

bool startsWith(const std::string& input, const std::string& prefix);
void decapitalize(std::string &str);
std::string remove_1st_word(std::string str);
bool is_inside(std::vector<std::string> vec, std::string to_find);
void remove_from_vec(std::vector<std::string>& vec, std::string to_remove);
bool is_first_wrd_capital(std::string str);
std::string format_client_reply(Client *client, int rpl_code, std::string msg);
std::string format_client_notice(Client* client, const std::string& msg);
std::vector<std::string> ft_split(const std::string &s, char delim);
bool check_valid_nickname(std::string nick);
bool check_valid_username(std::string user);
bool check_valid_realname(std::string rname);
bool check_valid_channel_name(std::string name);
std::string get_valid_realname(std::string rname);
std::string get_valid_username(std::string user);
long getTimestamp();
int ft_sto_ui(std::string str);
bool is_valid_mode(std::string mode);
std::string is_valid_topic(std::string topic);
//void init_bot(Client* bot);
void make_bot_speak(Client *bot, Server *server, Client *dest);
std::string get_valid_privmsg(std::string input);