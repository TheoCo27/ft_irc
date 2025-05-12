/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:09:46 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/12 20:23:16 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../includes/client.hpp"

class Channel
{
private:
	std::string name;
	std::vector<Client*> clients;
public:
	Channel(std::string name);
	~Channel();
	void addClient(Client* client);
	void removeClient(Client* client);
	void sendMessageToAllClients(const std::string& message);
	std::string getName() const;
	std::vector<Client*> getClients() const;
};