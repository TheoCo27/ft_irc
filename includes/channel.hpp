/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:09:46 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/15 19:08:58 by tcohen           ###   ########.fr       */
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
		int get_client_index(Client *client);
		void sendMessage(int client_fd, const std::string& message);
		std::string receiveMessage(int client_fd);
		//getters
		int getNbClient() const;
		std::string getName() const;
		//setters
		void setName(const std::string& name);
		void setNbClient(int nb_client);
};