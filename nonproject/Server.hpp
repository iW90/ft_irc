#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Socket.hpp"
# include "ServerException.hpp"
# include "Multiplexer.hpp"

# define MAX_EVENTS 20


class Multiplexer;

class Server
{
    private:
        int                     _fd;
        bool                    _running;
        const std::string       _password;
        Multiplexer             _multiplexer;

    public:
        Server(int socket_fd, const std::string& pass, Multiplexer multiplexer);
        ~Server();
        
        bool                is_running() const;
        int                 get_server_fd() const;
        const std::string   get_password() const;
        

        void    turn_on();
        void    turn_off();
};

#endif // SERVER_HPP
