#pragma once

#ifndef SERVER_SERVICE_HPP
# define SERVER_SERVICE_HPP

# include "irc_server/src/domain/exceptions/ServerException.hpp"
# include "irc_server/src/domain/entities/Server.cpp"
# include "irc_server/src/infrastructure/Socket.hpp"

# include <iostream>


class ServerService
{
    private:
        Server& server;
        Socket& socket;

        void configureSocket(const std::string& host, int port);
        void listenForConnections();

    public:
        ServerService(Server& serv, Socket& sock);
        ~ServerService();

        void start(const std::string& host, int port);
        void stop();
        
        void acceptConnection();
};

#endif // SERVER_SERVICE_HPP