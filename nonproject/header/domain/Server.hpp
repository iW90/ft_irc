#pragma once

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <set>
# include <map>

# include "interfaces/IVault.hpp"
# include "interfaces/ISocket.hpp"
# include "SignalManager.hpp"
# include "ServerException.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "Constants.hpp"
# include "Multiplexer.hpp"


class CommandHandler;
class IMultiplexer;
class Server {
    private:
        bool                        _running;
        IVault&                     _vault;
        ISocket&                    _socket;
        IMultiplexer&               _multiplexer;
        std::set<Channel* >         _channels;
        CommandHandler*             _command_handler;
        
    public:
        Server(IVault& vault, ISocket& socket, IMultiplexer& multiplexer);
        ~Server();

        // Getters
        IMultiplexer&                   get_multiplexer() const;

        const std::set<Channel*>&       get_channels() const;
        Channel*                        get_channel(const std::string& name);

        const std::map<int, Client*>&   get_clients() const;
        Client*                         get_client(const std::string& name);

        // Setters
        void                            set_command_handler(CommandHandler* handler);

        // Métodos
        void start();
        void stop();

        Channel*    create_channel(const std::string& name, const std::string& key, Client* client);
        bool        is_valid_pass(std::string pass);
};

#endif // SERVER_HPP
