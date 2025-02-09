#pragma once

#ifndef MULTIPLEXER_HPP
# define MULTIPLEXER_HPP

# include <iostream>        // Necessário para std::cout
# include <errno.h>         // Necessário para errno
# include <sys/epoll.h>     // Necessário para epoll
# include <unistd.h>        // Necessário para ::close()
# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para strstr() e bzero()

# define MAX_EVENTS 20
# define BUFFER_SIZE 100

class Multiplexer
{
    private:
        int                     _server_fd;
        int                     _epoll_fd;
        epoll_event             _events[MAX_EVENTS];

    public:
        Multiplexer(int server_fd);
        ~Multiplexer();

        void    subscribe_fd_for_monitoring(int fd);
        void    unsubscribe_fd_for_monitoring(int fd);
        void    check_for_events();

        void    handle_events(int total_events);

        void    connect_client(int server_fd);
        void    disconnect_client(int client_fd);
        void    read_client_message(int client_fd);
};



#endif //MULTIPLEXER_HPP