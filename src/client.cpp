/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:06 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/13 17:58:23 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client(int client_fd)
{
	this->_client_fd = client_fd;
	this->poll_fd.fd = client_fd;
	this->poll_fd.events = POLLIN;
	this->poll_fd.revents = 0;
	this->_nickname = "iencli";
	this->_username = "iencli42";
	this->status = UNAUTHORIZED;
}
Client::~Client(){}