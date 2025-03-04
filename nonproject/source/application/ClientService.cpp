#include "ClientService.hpp"


void ClientService::send_message(Client* client, const std::string& message) {
    Multiplexer::send_client_message(client->get_fd(), message);
}

void ClientService::reply_message(Client* client, const std::string& reply) {
    send_message(client, ":" + client->get_prefix() + " " + reply);
}

void ClientService::join_channel(Client* client, Channel* channel) {
    if (_add_client_to_channel(client, channel))
        _update_client_channel(client, channel);

    std::string users = _gather_channel_users(channel);
    
    _send_nickname_reply(client, channel, users);
    _send_end_of_names_reply(client, channel);
    _broadcast_join_message(client, channel);
}

void ClientService::leave_channel(Client* client) {
    Channel* channel = client->get_channel();
    if (!channel)
        return;

    ChannelService::remove_client(channel, client);
    client->set_channel(NULL);
}


// Funções auxiliares
bool ClientService::_add_client_to_channel(Client* client, Channel* channel) {
    return ChannelService::add_client(channel, client);
}


void ClientService::_update_client_channel(Client* client, Channel* channel) {
    client->set_channel(channel);
}

std::string ClientService::_gather_channel_users(Channel* channel) {
    std::string users = "";
    std::vector<std::string> nicknames = ChannelService::get_nicknames(channel);
    for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it) {
        users.append(*it + " ");
    }
    return users;
}

void ClientService::_send_nickname_reply(Client* client, Channel* channel, const std::string& users) {
    reply_message(client, RPL_NAMREPLY(client->get_nickname(), channel->get_name(), users));
}


void ClientService::_send_end_of_names_reply(Client* client, Channel* channel) {
    reply_message(client, RPL_ENDOFNAMES(client->get_nickname(), channel->get_name()));
}

void ClientService::_broadcast_join_message(Client* client, Channel* channel) {
    ChannelService::broadcast(channel, RPL_JOIN(client->get_prefix(), channel->get_name()));
}
