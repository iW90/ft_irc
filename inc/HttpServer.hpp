/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
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

#define DEFAULT_PORT 8080
#define MAX_BACKLOG 10
#define MAX_EVENTS 10

class HttpServer {
 public:
  HttpServer();
  ~HttpServer();
  HttpServer(const HttpServer& other);
  HttpServer& operator=(const HttpServer& other);

  void start();
  
 private:
  int server_fd;
  int epoll_fd;
  struct epoll_event epoll_event;
  sockaddr_in address;

  HttpServer& createServerSocket();
  HttpServer& bindSocket();
  HttpServer& listenForConnections();
  HttpServer& acceptConnections();

  HttpServer& createEpollInstance();
  HttpServer& addEpollEvent(int fd);
  HttpServer& handleEvents();
};
