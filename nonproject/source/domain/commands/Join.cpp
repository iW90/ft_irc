#include "commands/Join.hpp"


Join::Join(Server& server) : ACommand(server, true) {}
Join::~Join() {}


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
    return channel->get_limit() > 0 && channel->get_size() >= channel->get_limit();
}

bool Join::_is_channel_key_valid(Channel* channel, const std::string& pass) {
    return channel->get_key() == pass;
}


// syntax: JOIN <channel> [<key>]
void Join::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty()) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
        return;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

    // Verifica se o cliente já está em um canal
    if (_is_already_in_channel(client)) {
        ClientService::reply_message(client, ERR_TOOMANYCHANNELS(client->get_nickname(), name));
        return;
    }

    // Recupera ou cria o canal
    Channel* channel = _get_or_create_channel(name, pass, client);

    // Verifica se o canal está cheio
    if (_is_channel_full(channel)) {
        ClientService::reply_message(client, ERR_CHANNELISFULL(client->get_nickname(), name));
        return;
    }

    // Verifica se a senha do canal está correta
    if (!_is_channel_key_valid(channel, pass)) {
        ClientService::reply_message(client, ERR_BADCHANNELKEY(client->get_nickname(), name));
        return;
    }

    // Se todas as verificações passarem, o cliente entra no canal
    ClientService::join_channel(client, channel);
}
