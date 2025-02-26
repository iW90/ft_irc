#pragma once

#ifndef CLIENT_ACTION_MANAGER_HPP
# define CLIENT_ACTION_MANAGER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "ChannelManager.hpp"

# include <vector>

class Channel;
class Client;
class ClientActionManager
{
    public:
        static void send_message(Client* client, const std::string& message);
        static void reply_message(Client* client, const std::string& reply);

        static void join_channel(Client* client, Channel *channel);
        static void leave_channel(Client* client);

};

#endif // CLIENT_ACTION_MANAGER_HPP