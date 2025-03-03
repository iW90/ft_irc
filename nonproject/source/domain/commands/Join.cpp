#include "commands/Join.hpp"


Join::Join(Server& server) : ACommand(server, true) {}
Join::~Join() {}


// syntax: JOIN <channel> <key>
void Join::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

    if (_is_already_in_channel(client)) {
        ClientService::reply_message(client, ERR_TOOMANYCHANNELS(client->get_nickname(), name));
        return;
    }

    Channel* channel = _get_or_create_channel(name, pass, client);

    if (_is_channel_full(channel)) {
        ClientService::reply_message(client, ERR_CHANNELISFULL(client->get_nickname(), name));
        return;
    }

    if (!_is_channel_key_valid(channel, pass)) {
        ClientService::reply_message(client, ERR_BADCHANNELKEY(client->get_nickname(), name));
        return;
    }

    ClientService::join_channel(client, channel);
}


// Funções auxiliares

bool Join::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 1) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
        return false;
    }
    return true;
}

bool Join::_is_already_in_channel(Client* client) {
    return client->get_channel() != NULL;
}

Channel* Join::_get_or_create_channel(const std::string& name, const std::string& pass, Client* client) {
    Channel* channel = _server.get_channel(name);
    if (channel == NULL) {
        channel = _server.create_channel(name, pass, client);
    }
    return channel;
}

bool Join::_is_channel_full(Channel* channel) {
    return channel->get_limit() > 0 && channel->get_total_clients() >= channel->get_limit();
}

bool Join::_is_channel_key_valid(Channel* channel, const std::string& pass) {
    return channel->get_key() == pass;
}
