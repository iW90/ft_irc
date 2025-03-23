#pragma once

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <netinet/in.h>    // Necessário para sockaddr_in
# include <cstring>         // Necessário para memset()
# include <arpa/inet.h>     // Necessário para inet_ntoa / inet_addr
# include <stdexcept>       // Necessário para exceções
# include <string>          // Necessário para std::string

# include "Enums.hpp"


class Channel;

class Client {
    private:
        int                 _fd;
        struct sockaddr_in  _address;

        std::string         _nickname;
        std::string         _username;
        std::string         _hostname;
        std::string         _realname;

        ClientState         _state;

        Channel*            _channel;

    public:
        Client(int fd, const std::string& host, int port);
        ~Client();

        int         get_fd() const;
        std::string get_port() const;

        std::string get_nickname() const;
        std::string get_username() const;
        std::string get_hostname() const;
        std::string get_realname() const;
        std::string get_info() const;
        ClientState get_state() const;

        Channel*    get_channel() const;

        void set_nickname(const std::string& nickname);
        void set_username(const std::string& username);
        void set_realname(const std::string& nickname);
        void set_channel(Channel* channel);
        void set_state(ClientState state);
};

#endif // CLIENT_HPP
