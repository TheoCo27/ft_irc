/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:15:22 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/03 18:41:12 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>


bool startsWith(const std::string& input, const std::string& prefix);
void decapitalize(std::string &str);
std::string remove_1st_word(std::string str);
bool is_inside(std::vector<std::string> vec, std::string to_find);
void remove_from_vec(std::vector<std::string>& vec, std::string to_remove);