/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:43:58 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/17 19:21:02 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <unistd.h>

#define DEFAULT_PORT 6667
#define MAX_BACKLOG 10

class Server {
private:
    int server_fd;
    struct sockaddr_in address;

public:
    Server();
    Server(uint16_t port);
    Server(const Server& other);
    Server& operator=(const Server& other);
    ~Server();

    Server& setPort(uint16_t port);
    Server& createServerSocket();
    Server& bindSocket();
    Server& setSocketOptions();
    Server& listenForConnections();
    Server& useIPv6();
    void start();
};
