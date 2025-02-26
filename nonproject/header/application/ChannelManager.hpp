#pragma once

#ifndef CHANNEL_SERVICE_HPP
# define CHANNEL_SERVICE_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "ClientActionManager.hpp"

# include <vector>

class Channel;
class ChannelManager
{
    public:
        // Envio de mensagens no canal
        static void    broadcast(Channel* channel, const std::string& message);
        static void    broadcast(Channel* channel, const std::string& message, Client* exclude);

        // Gerenciamento de Clients no canal
        static void    add_client(Channel* channel, Client* client);
        static void    remove_client(Channel* channel, Client* client);
        static void    kick_client(Channel* channel, Client* client, Client* target, const std::string& reason);
};

#endif // CHANNEL_HPP