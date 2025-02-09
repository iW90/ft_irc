#pragma once

#ifndef MULTIPLEXER_HPP
# define MULTIPLEXER_HPP

# include <errno.h>
# include <sys/epoll.h>
# include <iostream>
# include <map>

# define MAX_EVENTS 20
# define BUFFER_SIZE 100

class Server;

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
        void    wait_for_events(Server& server);

        void    handle_events(int total_events);

        void    connect_client(int server_fd);
        void    disconnect_client(int client_fd);
        void    read_client_message(int client_fd);
};



#endif //MULTIPLEXER_HPP