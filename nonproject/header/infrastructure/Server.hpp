#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <set>

# include "Vault.hpp"
# include "Socket.hpp"
# include "Multiplexer.hpp"
# include "SignalManager.hpp"
# include "ServerException.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "Constants.hpp"


class Server
{
    private:
        bool                _running;
        Vault&              _vault;
        Socket&             _socket;
        Multiplexer&        _multiplexer;
        std::set<Channel *> _channels;
        std::set<Client *>  _clients;


    public:
        Server(Vault& vault, Socket& socket, Multiplexer& multiplexer);
        ~Server();

        // Getters
        const Vault& get_vault() const;
        const Socket& get_socket() const;
        const Multiplexer& get_multiplexer() const;
        const std::set<Channel*>& get_channels() const;
        const std::set<Client*>& get_clients() const;

        Channel* get_channel(const std::string& name);

        // Métodos
        void start();
        void stop();

        Channel*    create_channel(const std::string &name, const std::string &key, Client *client);
};

#endif // SERVER_HPP
