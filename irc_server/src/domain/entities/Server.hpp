#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <cstdint>
# include <arpa/inet.h>   // Necessário para inet_pton (converter string para binário)
# include <netinet/in.h>  // Necessário para sockaddr_in
# include <unistd.h>      // Necessário para close()
# include <stdexcept>     // Necessário para runtime_error()


class Server
{
    private:
        bool                running;        // Estado do servidor (rodando ou não)
        struct sockaddr_in  address;        // Configurações de porta e host
        int                 fdSocket;       // Socket do servidor

        /*
        struct sockaddr_in {
            sa_family_t    sin_family;   // Família de endereço (AF_INET para IPv4)
            in_port_t      sin_port;     // Porta (em formato de rede)
            struct in_addr sin_addr;     // Host do servidor (IP ou domínio)
        };
        */

    public:
        // Construtor e destruidor
        Server(const std::string& host, int port);
        ~Server();

        // Getters e Setters
        std::string getHost() const;
        void setHost(const std::string& host);

        int getPort() const;
        void setPort(int port);

        int getSocket() const;
        void setSocket(int socket);

        bool isRunning() const;
        void setRunning(bool running);
};

#endif //SERVER_HPP