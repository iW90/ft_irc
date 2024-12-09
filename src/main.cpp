#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    std::cerr << "Socket creation failed!" << std::endl;
    return 1;
  }

  sockaddr_in address;
  std::memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    std::cerr << "Binding failed!" << std::endl;
    return 1;
  }

  if (listen(server_fd, 1) == -1) {
      std::cerr << "Listen failed!" << std::endl;
      return 1;
  }

  int epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
      std::cerr << "Failed to create epoll instance!" << std::endl;
      return 1;
  }

  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = server_fd;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
    std::cerr << "Failed to add server_fd to epoll!" << std::endl;
    return 1;
  }

  while (true) {
    struct epoll_event events[MAX_EVENTS];
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (num_events == -1) {
        std::cerr << "epoll_wait failed!" << std::endl;
        return 1;
    }

    for (int i = 0; i < num_events; ++i) {
      if (events[i].data.fd == server_fd) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
          std::cerr << "Failed to accept client!" << std::endl;
          continue;
        }

        std::cout << "New client connected" << std::endl;

        event.events = EPOLLIN;
        event.data.fd = client_fd;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
          std::cerr << "Failed to add client_fd to epoll!" << std::endl;
          close(client_fd);
          continue;
        }
      } else if (events[i].events & EPOLLIN) {
        int client_fd = events[i].data.fd;
        char buffer[1024];
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) {
          std::cerr << "Failed to read from client!" << std::endl;
        } else if (bytes_read == 0) {
          std::cout << "Client disconnected" << std::endl;
          close(client_fd);
        } else {
          buffer[bytes_read] = '\0';
          std::cout << "Received request: " << buffer << std::endl;

          const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
          send(client_fd, response, std::strlen(response), 0);

          close(client_fd);
        }
      }
    }
  }

  close(server_fd);
  close(epoll_fd);
  return 0;
}
