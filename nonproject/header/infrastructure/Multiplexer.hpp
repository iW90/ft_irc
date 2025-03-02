#pragma once

#ifndef MULTIPLEXER_HPP
# define MULTIPLEXER_HPP

# include <iostream>        // Necessário para std::cout
# include <errno.h>         // Necessário para errno
# include <sys/epoll.h>     // Necessário para epoll
# include <unistd.h>        // Necessário para ::close()
# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para strstr() e bzero()
# include <map>             // Necessário para map<x,y>()

# include "Constants.hpp"

class Multiplexer
{
    private:
        int                     _server_fd;
        int                     _epoll_fd;
        epoll_event             _events[MAX_EVENTS];

    public:
        Multiplexer(int server_fd);
        ~Multiplexer();

        int     get_epoll_fd() const;

        void    subscribe_fd_for_monitoring(int fd);
        void    unsubscribe_fd_for_monitoring(int fd);

        int     check_for_events();
        void    handle_events(int total_events);

        int     connect_client(int server_fd);
        void    disconnect_client(int client_fd);
        void    read_client_message(int client_fd);
        
        static void    send_client_message(int client_fd, const std::string& message);


        // MÉTODOS AINDA NÃO UTILIZADOS
        void    handle_read_event(int fd);
        void    handle_write_event(int fd);
        void    handle_error_event(int fd);
        void    handle_hangup_event(int fd);
};

#endif //MULTIPLEXER_HPP