#pragma once

#ifndef SERVER_SERVICE_HPP
#define SERVER_SERVICE_HPP

#include "Server.hpp"
#include "Socket.hpp"
#include "ServerException.hpp"

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