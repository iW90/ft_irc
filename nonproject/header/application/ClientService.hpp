#pragma once

#ifndef CLIENT_ACTION_MANAGER_HPP
# define CLIENT_ACTION_MANAGER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "ChannelService.hpp"
# include "Multiplexer.hpp"

# include <vector>


class ClientService {
    private:
        static bool         _add_client_to_channel(Client* client, Channel* channel);
        static void         _update_client_channel(Client* client, Channel* channel);
        static std::string  _gather_channel_users(Channel* channel);
        static void         _send_nickname_reply(Client* client, Channel* channel, const std::string& users);
        static void         _send_end_of_names_reply(Client* client, Channel* channel);
        static void         _broadcast_join_message(Client* client, Channel* channel);

    public:
        static void         send_message(Client* client, const std::string& message);
        static void         reply_message(Client* client, const std::string& reply);

        static void         join_channel(Client* client, Channel* channel);
        static void         leave_channel(Client* client);
};

#endif // CLIENT_ACTION_MANAGER_HPP