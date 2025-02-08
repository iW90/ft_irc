#pragma once

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para memset()
# include <string>

# define MAX_CONNECTIONS 20

class Client
{
    private:
        int                 _fd;
        struct sockaddr_in  _address;

    public:
        Client(int fd, const std::string& host, int port);
        ~Client();
};

#endif // CLIENT_HPP
