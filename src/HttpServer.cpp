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
  address.sin_port = htons(DEFAULT_PORT);
}

HttpServer::~HttpServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
}

HttpServer& HttpServer::createServerSocket() {
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    throw std::runtime_error("Failed to create socket");
  }
  return *this;
}

HttpServer& HttpServer::bindSocket() {
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    throw std::runtime_error("Failed to bind socket");
  }
  return *this;
}

HttpServer& HttpServer::listenForConnections() {
  if (listen(server_fd, MAX_BACKLOG) == -1) {
    throw std::runtime_error("Failed to listen on socket");
  }
  return *this;
}

void HttpServer::start() {
  createServerSocket().bindSocket().listenForConnections();
}
