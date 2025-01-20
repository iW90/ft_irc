#pragma once

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <unistd.h>        // Necessário para close()
# include <cstring>         // Necessário para memset()
# include <fcntl.h>         // Necessário para fcntl e suas constantes
# include <arpa/inet.h>     // Necessário para inet_ntoa / inet_addr
# include <stdexcept>       // Necessário para exceções

class Socket
{
    private:
        int     socketFD;

    public:
        Socket();
        ~Socket();

        int     getSocket() const;
        void    setSocket(int socket);

        // Funções para controle do socket
        void    create();
        void    bind(const struct sockaddr_in& address);
        void    listen(int backlog);
        int     accept(struct sockaddr_in& clientAddress, socklen_t& clientAddrLen);
        void    close();

        // Funções de configuração
        void    setNonBlocking();
        void    configure(const std::string& host, int port);
};

#endif // SOCKET_HPP
