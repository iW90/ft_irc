#include "commands/general/Join.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientService.hpp"
#include "ChannelService.hpp"
#include "Macros.hpp"
#include "Server.hpp"

Join::Join(Server* server) : ACommand(server, true) {}
Join::~Join() {}


// syntax: JOIN <channel> <key>
//         JOIN <channel>
void Join::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

    if (_is_already_in_channel(client, name))
        return;

    Channel* channel = _get_or_create_channel(name, pass, client);

    if (_is_channel_full(channel, client, name))
        return;

    if (!_is_channel_key_valid(channel, client, pass, name))
        return;

    ClientService::join_channel(client, channel);
}


// Funções auxiliares

bool Join::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() > 0)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
    return false;
}

bool Join::_is_already_in_channel(Client* client, std::string name) {
    if (client->get_channel() == NULL)
        return false;
    ClientService::reply_message(client, ERR_TOOMANYCHANNELS(client->get_nickname(), name));
    return true;
}

Channel* Join::_get_or_create_channel(const std::string& name, const std::string& pass, Client* client) {
    Channel* channel = _server->get_channel(name);
    if (channel == NULL)
        channel = _server->create_channel(name, pass, client);
    return channel;
}

bool Join::_is_channel_full(Channel* channel, Client* client, const std::string& name) {

    if (channel->get_limit().first && ChannelService::get_total_clients(channel) < channel->get_limit().second)
        return false;

    ClientService::reply_message(client, ERR_CHANNELISFULL(client->get_nickname(), name));
    return true;
}

bool Join::_is_channel_key_valid(Channel* channel, Client* client, const std::string& pass, std::string name) {
    if (channel->get_key().first && channel->get_key().second == pass)
        return true;
    ClientService::reply_message(client, ERR_BADCHANNELKEY(client->get_nickname(), name));
    return false;
}
