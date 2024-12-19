/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:05:49 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/17 19:21:13 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <arpa/inet.h>

HttpServer::HttpServer() : server_fd(-1) {
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  setPort(DEFAULT_PORT);
}

HttpServer::HttpServer(uint16_t port) : server_fd(-1) {
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  setPort(port);
}

HttpServer::HttpServer(const HttpServer& other) : server_fd(-1) {
  std::memcpy(&address, &other.address, sizeof(address));
  address.sin_port = 0;

  uint16_t new_port = other.address.sin_port == 0 ? DEFAULT_PORT : ntohs(other.address.sin_port) + 1;
  setPort(new_port);
}

HttpServer& HttpServer::operator=(const HttpServer& other) {
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


HttpServer::~HttpServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
}

HttpServer& HttpServer::setPort(uint16_t port) {
  address.sin_port = htons(port);
  return *this;
}


HttpServer& HttpServer::createServerSocket() {
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    throw std::runtime_error("Http server failed to create socket");
  }
  return *this;
}

HttpServer& HttpServer::bindSocket() {
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    throw std::runtime_error("Http server failed to bind socket");
  }
  return *this;
}

HttpServer& HttpServer::bindSocket() {
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    throw std::runtime_error("Http server failed to bind socket");
  }

  socklen_t len = sizeof(address);
  if (getsockname(server_fd, (struct sockaddr*)&address, &len) == -1) {
    throw std::runtime_error("Http server failed to retrieve assigned port");
  }
  return *this;
}


HttpServer& HttpServer::setSocketOptions() {
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    throw std::runtime_error("Http server failed to set socket options");
  }
  return *this;
}

HttpServer& HttpServer::listenForConnections() {
  if (listen(server_fd, MAX_BACKLOG) == -1) {
    throw std::runtime_error("Http server failed to listen on socket");
  }
  return *this;
}

void HttpServer::start() {
  createServerSocket().setSocketOptions().bindSocket().listenForConnections();
}

HttpServer& HttpServer::useIPv6() {
  address.sin_family = AF_INET6;
  return *this;
}
