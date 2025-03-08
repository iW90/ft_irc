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
    std::string pass = args.size() == 2 ? args[1] : "";

    if (_is_already_in_channel(client, name))
        return;

    Channel* channel = _get_or_create_channel(name, client);

    if (_is_channel_full(channel, client, name))
        return;

    if (!_is_channel_key_valid(channel, client, pass, name))
        return;

    if (channel->get_admin() == NULL)
        channel->set_admin(client);

    std::cout << "JOIN::Add client..." << std::endl;
    if (ChannelService::add_client(channel, client))
        ClientService::join_channel(client, channel);
    std::cout << "SUCCEDED JOIN" << std::endl;
}


// Funções auxiliares

bool Join::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    std::cout << "JOIN::Validate parameters..." << std::endl;
    if (args.size() == 1 || args.size() == 2)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
    return false;
}

bool Join::_is_already_in_channel(Client* client, std::string name) {
    std::cout << "JOIN::Validate if is already in channel..." << std::endl;
    if (client->get_channel() == NULL)
        return false;
    ClientService::reply_message(client, ERR_TOOMANYCHANNELS(client->get_nickname(), name));
    return true;
}

Channel* Join::_get_or_create_channel(const std::string& name, Client* client) {
    std::cout << "JOIN::Get or create channel..." << std::endl;
    Channel* channel = _server->get_channel(name);
    if (channel == NULL)
        channel = _server->create_channel(name, client);
    return channel;
}

bool Join::_is_channel_full(Channel* channel, Client* client, const std::string& name) {
    std::cout << "JOIN::Validate if channel is full..." << std::endl;
    if (channel->get_limit().first && ChannelService::get_total_clients(channel) >= channel->get_limit().second) {
        ClientService::reply_message(client, ERR_CHANNELISFULL(client->get_nickname(), name));
        return true;
    }
    return false;
}

bool Join::_is_channel_key_valid(Channel* channel, Client* client, const std::string& pass, std::string name) {
    std::cout << "JOIN::Validate if key correct..." << std::endl;
    if (!channel->get_key().first || (channel->get_key().first && channel->get_key().second == pass))
        return true;
    ClientService::reply_message(client, ERR_BADCHANNELKEY(client->get_nickname(), name));
    return false;
}
