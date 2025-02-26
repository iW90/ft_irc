#include "ClientActionManager.hpp"


void ClientActionManager::send_message(Client* client, const std::string& message) {
    std::string buffer = message + "\r\n";
    if (send(client->get_fd(), buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
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
