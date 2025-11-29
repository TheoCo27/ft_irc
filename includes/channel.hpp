/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:09:46 by tcohen            #+#    #+#             */
/*   Updated: 2025/11/29 20:31:35 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"
#include <ctime>
//#include "utils.hpp"

class Channel
{
	private:
		std::string name;
		std::vector<Client*> clients;
		int nb_client;
		std::string password;
		std::string topic;
		std::vector<Client *> operators;
		std::vector<std::string> invited_nick;
		bool topic_restricted;
		bool has_password;
		bool has_limit_user;
		bool invite_only;
		int limit_user;
		time_t creation_time;



	public:
		Channel(std::string name);
		~Channel();
		void addClient(Client* client);
		void removeClient(Client* client);
		void sendMessageToAllClients(const std::string& message, Client *client);
		int get_client_index(Client *client);
		void sendMessage(int client_fd, const std::string& message);
		std::string receiveMessage(int client_fd);
		void remove_op(Client *client);

		//getters
		int getNbClient() const;
		std::string getName() const;
		std::string get_pass();
		std::string get_topic();
		std::vector<Client *>& get_operators();
		std::vector<std::string>& get_invited_nick();
		bool is_topic_restricted();
		bool check_has_password();
		bool check_has_limit_user();
		bool is_invite_only();
		int get_limit_user();
		std::time_t get_creation_time();
		std::string get_client_list();
		bool is_op(Client *client);
		bool is_client(Client *client);
		std::string get_mode_list();
		//setters
		void setName(const std::string& name);
		void setNbClient(int nb_client);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_topic_restricted(bool is_restricted);
		void set_has_password(bool has_pass);
		void set_has_limit_user(bool has_limit_user);
		void set_invite_only(bool is_invite_only);
		void set_limit_user(int limit_user);
};