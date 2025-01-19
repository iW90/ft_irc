#pragma once

#ifndef SERVERSETUP_HPP
# define SERVERSETUP_HPP

# include "irc_server/src/domain/entities/Server.cpp"
# include "irc_server/src/domain/exceptions/ServerExceptions.hpp"

# include <iostream>
# include <fcntl.h>         // Necessário para fcntl e suas const
# include <arpa/inet.h>     // Necessário para inet_ntoa / inet_addr

class ServerManager
{
    private:
        Server& server;
        
    public:
        ServerManager(Server& serv);
        ~ServerManager();

        // Funções para controle do servidor
        void start(const std::string& host, int port);
        void stop();

        // Funções auxiliares para configuração e gerenciamento do servidor
        void configureSocket(const std::string& host, int port);
        void bindSocket();
        void listenForConnections();
        void acceptConnection();
        void setSocketNonBlocking();
        void closeSocket();
};

#endif // SERVERSETUP_HPP
