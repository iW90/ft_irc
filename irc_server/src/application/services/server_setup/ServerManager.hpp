#pragma once

#ifndef SERVERSETUP_HPP
# define SERVERSETUP_HPP

#include "Server.hpp"

#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>

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
