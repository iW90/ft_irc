/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:43:58 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/16 21:16:58 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <vector>

#define MAX_BACKLOG 10
#define MAX_EVENTS 10

class Multiplexer {
 public:
  Multiplexer();
  ~Multiplexer();
  Multiplexer(const Multiplexer& other);
  Multiplexer& operator=(const Multiplexer& other);


 private:
  int epoll_fd;
  struct epoll_event epoll_event;

  void addSocket(int fd, uint32_t events);
  void removeSocket(int fd);
  std::vector<struct epoll_event> waitForEvents(int max_events, int timeout = -1);
};
