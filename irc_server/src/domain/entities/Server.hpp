#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <unistd.h>        // Necessário para close()
# include <cstring>         // Necessário para memset()


class Server
{
    private:
        bool                running;        // Estado do servidor (rodando ou não)
        struct sockaddr_in  address;        // Configurações de porta e host
        int                 fdServer;       // FD do socket do servidor

        /*
        struct sockaddr_in {
            sa_family_t    sin_family;   // Família de endereço (AF_INET para IPv4)
            in_port_t      sin_port;     // Porta (em formato de rede)
            struct in_addr sin_addr;     // Host do servidor (IP ou domínio)
        };
        */

    public:
        // Construtor e destruidor
        Server();
        ~Server();

        // Getters e Setters
        sockaddr_in getAddress() const;
        void setAddress(const sockaddr_in& addr);

        int getSocket() const;
        void setSocket(int socket);

        bool isRunning() const;
        void setRunning(bool runn);


};

#endif //SERVER_HPP