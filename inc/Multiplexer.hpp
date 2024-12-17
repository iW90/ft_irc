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

#include <sys/epoll.h>

#define MAX_BACKLOG 10
#define MAX_EVENTS 10

class Multiplexer {
 public:
  Multiplexer();
  ~Multiplexer();
  Multiplexer(const Multiplexer& other);
  Multiplexer& operator=(const Multiplexer& other);

  void start(int server_fd);
  
 private:
  int epoll_fd;
  struct epoll_event epoll_event;

  Multiplexer& createEpollInstance(int server_fd);
  Multiplexer& addEpollEvent(int fd);
  Multiplexer& handleEvents(int server_fd);
  Multiplexer& acceptConnections(int server_fd);
};
