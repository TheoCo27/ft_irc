/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:34:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/05/13 17:51:05 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"
#include "../includes/client.hpp"
#include "../includes/channel.hpp"

int main(int argc, char** argv)
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <port>  <password> " << std::endl;
		return EXIT_FAILURE;
	}
	int port = atoi(argv[1]);
	if (port <= 0 || port > 65535) {
		std::cerr << "Port must be between 1 and 65535." << std::endl;
		return EXIT_FAILURE;
	}
	Server server(port, argv[2]);
	server.init();
	server.start();
	return EXIT_SUCCESS;
}
// 	this->poll_fds.push_back(server_poll_fd);
