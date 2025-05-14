/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:09:46 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/14 16:33:35 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"

class Channel
{
	private:
		std::string name;
		std::vector<Client*> clients;
		int nb_client;
	public:
		Channel(std::string name);
		~Channel();
		void addClient(Client* client);
		void removeClient(Client* client);
		void sendMessageToAllClients(const std::string& message, Client *client);
		std::string getName() const;
		std::vector<Client*> getClients() const;
		int get_client_index(Client *client);
		void sendMessage(int client_fd, const std::string& message);
		std::string receiveMessage(int client_fd);
};