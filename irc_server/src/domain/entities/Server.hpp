#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para memset()


class Server
{
    private:
        bool                running;
        struct sockaddr_in  address;

        /*
        struct sockaddr_in {
            sa_family_t    sin_family;   // Família de endereço (AF_INET para IPv4)
            in_port_t      sin_port;     // Porta (em formato de rede)
            struct in_addr sin_addr;     // Host do servidor (IP ou domínio)
        };
        */

    public:
        Server();
        ~Server();

        // Getters e Setters
        struct sockaddr_in  getAddress() const;
        void                setAddress(const struct sockaddr_in& addr);

        bool                isRunning() const;
        void                setRunning(bool runn);
};

#endif // SERVER_HPP
