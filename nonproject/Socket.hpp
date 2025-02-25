#pragma once

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <unistd.h>        // Necessário para close()
# include <cstring>         // Necessário para memset()
# include <fcntl.h>         // Necessário para fcntl e suas constantes
# include <arpa/inet.h>     // Necessário para inet_ntoa / inet_addr
# include <stdexcept>       // Necessário para exceções

# define MAX_CONNECTIONS 20

class Socket
{
    private:
        int                 _socket_fd;
        struct sockaddr_in  _address;
        int                 _max_connections;
        /*
            struct sockaddr_in {
                sa_family_t    sin_family;   // Família de endereço (AF_INET para IPv4)
                in_port_t      sin_port;     // Porta (em formato de rede)
                struct in_addr sin_addr;     // Host do servidor (IP ou domínio)
            };
        */

        // Funções de configuração
        void    _create_socket();
        void    _configure_socket();
        void    _set_non_blocking();
        void    _configure_address(const std::string& host, int port);
        void    _bind_socket_to_address();
        void    _set_listening();

    public:
        Socket(const std::string& host, int port);
        ~Socket();

        int     get_fd() const;
};

#endif // SOCKET_HPP
