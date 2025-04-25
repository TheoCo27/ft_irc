/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:34:52 by tcohen            #+#    #+#             */
/*   Updated: 2025/04/25 17:41:40 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio> 
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>

#define PORT 6667
#define BUFFER_SIZE 512

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("listen");
        return 1;
    }

    std::cout << "🟢 Serveur IRC en écoute sur le port " << PORT << std::endl;

    std::vector<struct pollfd> poll_fds;

    struct pollfd server_poll_fd;
    server_poll_fd.fd = server_fd;
    server_poll_fd.events = POLLIN;
    server_poll_fd.revents = 0;

    poll_fds.push_back(server_poll_fd);

    char buffer[BUFFER_SIZE];

    while (true) {
        int activity = poll(&poll_fds[0], poll_fds.size(), -1);
        if (activity < 0) {
            perror("poll");
            continue;
        }

        for (size_t i = 0; i < poll_fds.size(); ++i) {
            if (poll_fds[i].revents & POLLIN) {
                if (poll_fds[i].fd == server_fd) {
                    // Nouvelle connexion
                    int client_fd = accept(server_fd, NULL, NULL);
                    if (client_fd >= 0) {
                        std::cout << "👤 Nouveau client connecté (fd: " << client_fd << ")" << std::endl;
                        struct pollfd client_poll_fd;
                        client_poll_fd.fd = client_fd;
                        client_poll_fd.events = POLLIN;
                        client_poll_fd.revents = 0;
                        poll_fds.push_back(client_poll_fd);
                    }
                } else {
                    // Message d'un client
                    ssize_t bytes = recv(poll_fds[i].fd, buffer, BUFFER_SIZE - 1, 0);
                    if (bytes <= 0) {
                        std::cout << "❌ Client déconnecté (fd: " << poll_fds[i].fd << ")" << std::endl;
                        close(poll_fds[i].fd);
                        poll_fds.erase(poll_fds.begin() + i);
                        --i;
                    } else {
                        buffer[bytes] = '\0';
                        std::cout << "📩 Reçu du client " << poll_fds[i].fd << " : " << buffer;
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
