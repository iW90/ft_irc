/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:05:49 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/16 21:19:24 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"
#include <cstring>
#include <unistd.h>
#include <stdexcept>

HttpServer::HttpServer() : server_fd(-1), epoll_fd(-1) {
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(DEFAULT_PORT);
}

HttpServer::~HttpServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
  if (epoll_fd != -1) {
    close(epoll_fd);
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

HttpServer& HttpServer::acceptConnections() {
  int client_fd = accept(server_fd, NULL, NULL);
  if (client_fd == -1) {
    throw std::runtime_error("Failed to accept connection");
  }
  addEpollEvent(client_fd);
  return *this;
}

HttpServer& HttpServer::createEpollInstance() {
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    throw std::runtime_error("Failed to create epoll instance");
  }
  epoll_event.events = EPOLLIN;
  epoll_event.data.fd = server_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &epoll_event) == -1) {
    throw std::runtime_error("Failed to add server socket to epoll");
  }
  return *this;
}

HttpServer& HttpServer::addEpollEvent(int fd) {
  epoll_event.events = EPOLLIN;
  epoll_event.data.fd = fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &epoll_event) == -1) {
    throw std::runtime_error("Failed to add socket to epoll");
  }
  return *this;
}

HttpServer& HttpServer::handleEvents() {
  struct epoll_event events[MAX_EVENTS];
  int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
  if (num_events == -1) {
    throw std::runtime_error("epoll_wait failed");
  }

  for (int i = 0; i < num_events; ++i) {
    if (events[i].data.fd == server_fd) {
      acceptConnections();
    } else {
      // Handle data for existing connection (not implemented here)
    }
  }
  return *this;
}

void HttpServer::start() {
  createServerSocket().bindSocket().listenForConnections().createEpollInstance().handleEvents();
}
