/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:43:58 by maalexan          #+#    #+#             */
/*   Updated: 2024/12/17 19:21:02 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define DEFAULT_PORT 8080
#define MAX_BACKLOG 10

class HttpServer {
 public:
  HttpServer();
  HttpServer(uint16_t port);
  ~HttpServer();
  HttpServer(const HttpServer& other);
  HttpServer& operator=(const HttpServer& other);

  void start();
  HttpServer& useIPv6();
  
 private:
  int server_fd;
  sockaddr_in address;

  HttpServer& setPort(uint16_t port);
  HttpServer& createServerSocket();
  HttpServer& setSocketOptions ();
  HttpServer& bindSocket();
  HttpServer& listenForConnections();

};
