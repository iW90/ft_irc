#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include "Socket.hpp"
# include "Multiplexer.hpp"
# include "ServerException.hpp"
# include "Client.hpp"

# define MAX_EVENTS 20


class Multiplexer;
class Server : private Socket
{
    private:
        bool                    _running;
        const std::string       _password;
        Multiplexer             _multiplexer;

    public:
        Server(const std::string& host, int port, const std::string& pass);
        ~Server();
        
        bool    is_running() const;
        int     get_server_fd() const;
        const std::string get_password() const;
        

        void    turn_on_server();
        void    turn_off_server();
};

#endif // SERVER_HPP
