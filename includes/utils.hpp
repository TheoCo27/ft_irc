/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:15:22 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/20 17:33:28 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "client.hpp"
#include <sstream>


bool startsWith(const std::string& input, const std::string& prefix);
void decapitalize(std::string &str);
std::string remove_1st_word(std::string str);
bool is_inside(std::vector<std::string> vec, std::string to_find);
void remove_from_vec(std::vector<std::string>& vec, std::string to_remove);
bool is_first_wrd_capital(std::string str);
std::string format_client_reply(Client *client, int rpl_code, std::string msg);
std::vector<std::string> ft_split(const std::string &s, char delim);
bool check_valid_nickname(std::string nick);