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

Multiplexer::Multiplexer() : epoll_fd(-1) {
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    throw std::runtime_error("Failed to create epoll instance");
  }
}

Multiplexer::~Multiplexer() {
  if (epoll_fd != -1) {
    close(epoll_fd);
  }
}

void Multiplexer::addSocket(int fd, uint32_t events) {
    struct epoll_event ev{};
    ev.events = events;
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
      throw std::runtime_error("Failed to add socket to epoll");
    }
}

void Multiplexer::removeSocket(int fd) {
    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
      throw std::runtime_error("Failed to remove socket from epoll");
    }
}

std::vector<epoll_event> Multiplexer::waitForEvents(int max_events, int timeout = -1) {
    std::vector<struct epoll_event> events(max_events);
    int num_events = epoll_wait(epoll_fd, events.data(), max_events, timeout);
    if (num_events == -1) {
      throw std::runtime_error("epoll_wait failed");
    }
    events.resize(num_events);
    return events;
}
