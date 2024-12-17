/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:05:49 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/16 21:19:24 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Multiplexer.hpp"
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <arpa/inet.h>

Multiplexer::Multiplexer() : epoll_fd(-1) {
}

Multiplexer::~Multiplexer() {
  if (epoll_fd != -1) {
    close(epoll_fd);
  }
}


Multiplexer& Multiplexer::acceptConnections(int server_fd) {
  int client_fd = accept(server_fd, NULL, NULL);
  if (client_fd == -1) {
    throw std::runtime_error("Failed to accept connection");
  }
  addEpollEvent(client_fd);
  return *this;
}

Multiplexer& Multiplexer::createEpollInstance(int server_fd) {
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

Multiplexer& Multiplexer::addEpollEvent(int fd) {
  epoll_event.events = EPOLLIN;
  epoll_event.data.fd = fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &epoll_event) == -1) {
    throw std::runtime_error("Failed to add socket to epoll");
  }
  return *this;
}

Multiplexer& Multiplexer::handleEvents(int server_fd) {
  struct epoll_event events[MAX_EVENTS];
  int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
  if (num_events == -1) {
    throw std::runtime_error("epoll_wait failed");
  }

  for (int i = 0; i < num_events; ++i) {
    if (events[i].data.fd == server_fd) {
      acceptConnections(server_fd);
    } else {
      // Handle data for existing connection (not implemented here)
    }
  }
  return *this;
}

void Multiplexer::start(int server_fd) {
  createEpollInstance(server_fd).handleEvents(server_fd);
}
