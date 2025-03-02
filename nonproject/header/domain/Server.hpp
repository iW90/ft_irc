#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <set>

# include "interfaces/IVault.hpp"
# include "interfaces/ISocket.hpp"
# include "interfaces/IMultiplexer.hpp"
# include "SignalManager.hpp"
# include "ServerException.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "Constants.hpp"


class Server {
    private:
        bool                _running;
        IVault&              _vault;
        ISocket&             _socket;
        IMultiplexer&        _multiplexer;
        std::set<Channel *> _channels;
        std::set<Client *>  _clients;


    public:
        Server(IVault& vault, ISocket& socket, IMultiplexer& multiplexer);
        ~Server();

        // Getters
        const IVault& get_vault() const;
        const ISocket& get_socket() const;
        const IMultiplexer& get_multiplexer() const;
        const std::set<Channel*>& get_channels() const;
        const std::set<Client*>& get_clients() const;

        Channel* get_channel(const std::string& name);

        // Métodos
        void start();
        void stop();

        Channel*    create_channel(const std::string &name, const std::string &key, Client *client);
};

#endif // SERVER_HPP
