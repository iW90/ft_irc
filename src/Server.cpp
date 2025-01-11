/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:05:49 by maalexan          #+#    #+#             */
/*   Updated: 2025/01/11 10:33:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

Server::Server() : server_fd(-1) {
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    setPort(DEFAULT_PORT);
}

Server::Server(uint16_t port) : server_fd(-1) {
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    setPort(port);
}

Server::Server(const Server& other) : server_fd(-1) {
    std::memcpy(&address, &other.address, sizeof(address));
    address.sin_port = 0;

    uint16_t new_port = other.address.sin_port == 0 ? DEFAULT_PORT : ntohs(other.address.sin_port) + 1;
    setPort(new_port);
}

Server& Server::operator=(const Server& other) {
    if (this != &other) {
        if (server_fd != -1) {
            close(server_fd);
        }
        std::memcpy(&address, &other.address, sizeof(address));
        address.sin_port = 0;

        uint16_t new_port = other.address.sin_port == 0 ? DEFAULT_PORT : ntohs(other.address.sin_port) + 1;
        setPort(new_port);
        server_fd = -1;
    }
    return *this;
}

Server::~Server() {
    if (server_fd != -1) {
        close(server_fd);
    }
}

Server& Server::setPort(uint16_t port) {
    address.sin_port = htons(port);
    return *this;
}

Server& Server::createServerSocket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::runtime_error("IRC server failed to create socket");
    }
    return *this;
}

Server& Server::bindSocket() {
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        throw std::runtime_error("IRC server failed to bind socket");
    }

    socklen_t len = sizeof(address);
    if (getsockname(server_fd, (struct sockaddr*)&address, &len) == -1) {
        throw std::runtime_error("IRC server failed to retrieve assigned port");
    }
    return *this;
}

Server& Server::setSocketOptions() {
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        throw std::runtime_error("IRC server failed to set socket options");
    }
    return *this;
}

Server& Server::listenForConnections() {
    if (listen(server_fd, MAX_BACKLOG) == -1) {
        throw std::runtime_error("IRC server failed to listen on socket");
    }
    return *this;
}

Server& Server::useIPv6() {
    address.sin_family = AF_INET6;
    return *this;
}

void Server::start() {
    createServerSocket().setSocketOptions().bindSocket().listenForConnections();
}
