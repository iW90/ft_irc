#include "ClientActionManager.hpp"

// ENVIA UMA MENSAGEM
void ClientActionManager::send_message(Client* client, const std::string& message) {
    Multiplexer::send_client_message(client->get_fd(), message);
}

void ClientActionManager::reply_message(Client* client, const std::string& reply) {
    send_message(client, ":" + client->get_nickname() + " " + reply);
}

void ClientActionManager::join_channel(Client* client, Channel *channel) {
    ChannelManager::add_client(channel, client);
    client->set_channel(channel);
}

void ClientActionManager::leave_channel(Client* client) {
    Channel* channel = client->get_channel();
    if (!channel)
        return;

    ChannelManager::add_client(channel, client);
}
