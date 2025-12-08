/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:34:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/12/08 18:41:59 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"
#include "../includes/client.hpp"
#include "../includes/channel.hpp"
#include "../includes/utils.hpp"
#include <csignal>

Server *get_server(Server *ptr, bool reset_static)
{
	static Server* server;

	if(ptr != NULL)
		server = ptr;
	if(reset_static)
		server = NULL;
	return server;

}

void sigint_handler(int sig)
{
	if(sig != SIGINT)
		return;
	std::cout << "\n❌ Serveur interrompu par Ctrl+C. Fermeture propre...\n";
	Server *server = get_server(NULL, 0);
	if (server)
		server->~Server();  // ou une fonction qui ferme tous les clients + sockets
	get_server(NULL, 1);
	exit(0);
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <port>  <password> " << std::endl;
		return EXIT_FAILURE;
	}
	int port = ft_sto_ui(argv[1]);
	if (port <= 0 || port > 65535) {
		std::cerr << "Port must be between 1 and 65535." << std::endl;
		return EXIT_FAILURE;
	}
	std::string pass(argv[2]);
	if(pass.empty() || check_valid_realname(pass) == false)
	{
		std::cerr << "Invalid password" << std::endl;
		return EXIT_FAILURE;
	}
	Server server(port, argv[2]);
	get_server(&server, 0);
	std::signal(SIGINT, sigint_handler);
	server.init();
	server.start();
	return EXIT_SUCCESS;
}
