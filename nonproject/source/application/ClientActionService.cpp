#include "ClientActionService.hpp"

// ENVIA UMA MENSAGEM
void ClientActionService::send_message(Client* client, const std::string& message) {
    Multiplexer::send_client_message(client->get_fd(), message);
}

void ClientActionService::reply_message(Client* client, const std::string& reply) {
    send_message(client, ":" + client->get_nickname() + " " + reply);
}

void ClientActionService::join_channel(Client* client, Channel *channel) {
    ChannelService::add_client(channel, client);
    client->set_channel(channel);
}

void ClientActionService::leave_channel(Client* client) {
    Channel* channel = client->get_channel();
    if (!channel)
        return;

    ChannelService::add_client(channel, client);
}
