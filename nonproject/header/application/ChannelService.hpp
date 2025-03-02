#pragma once

#ifndef CHANNEL_SERVICE_HPP
# define CHANNEL_SERVICE_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "ClientService.hpp"

# include <set>

class Channel;
class ChannelService
{
    private:
        static void    _change_admin_if_needed(Channel* channel, Client* client);

    public:
        // Envio de mensagens no canal
        static void    broadcast(Channel* channel, const std::string& message, Client* exclude = NULL);

        // Gerenciamento de Clients no canal
        static void    add_client(Channel* channel, Client* client);
        static void    remove_client(Channel* channel, Client* client);
        static void    kick_client(Channel* channel, Client* client, Client* target, const std::string& reason);
};

#endif // CHANNEL_HPP