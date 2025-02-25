#pragma once

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para memset()
# include <arpa/inet.h>     // Necessário para inet_ntoa / inet_addr
# include <stdexcept>       // Necessário para exceções
# include <string>

# define MAX_CONNECTIONS 20

class Channel;
class Client
{
    private:
        int                 _fd;
        struct sockaddr_in  _address;

        std::string     _nickname;
        std::string     _username;
        std::string     _hostname;

        std::string     _state;
        Channel*        _channel;

    public:
        Client(int fd, const std::string& host, int port);
        ~Client();

        int get_fd() const;
        std::string get_port() const;

        std::string get_nickname() const;
        std::string get_username() const;
        std::string get_hostname() const;

        bool        is_registered() const;
        Channel*    get_channel() const;

        void set_nickname(const std::string &nickname);
        void set_username(const std::string &username);
        void set_state(std::string state);
        void set_channel(Channel *channel);
};

#endif // CLIENT_HPP
