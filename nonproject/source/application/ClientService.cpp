#include "ClientService.hpp"


void ClientService::send_message(Client* client, const std::string& message) {
    Multiplexer::send_client_message(client->get_fd(), message);
}

void ClientService::reply_message(Client* client, const std::string& reply) {
    send_message(client, ":" + client->get_nickname() + " " + reply);
}

void ClientService::join_channel(Client* client, Channel *channel) {
    if (ChannelService::add_client(channel, client))
        client->set_channel(channel);
}

void ClientService::leave_channel(Client* client) {
    Channel* channel = client->get_channel();
    if (!channel)
        return;

    ChannelService::remove_client(channel, client);
    client->set_channel(NULL);
}
