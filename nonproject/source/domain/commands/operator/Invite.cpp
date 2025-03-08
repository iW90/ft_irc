#include "commands/operator/Invite.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientService.hpp"
#include "ChannelService.hpp"
#include "Macros.hpp"
#include "Server.hpp"


Invite::Invite(Server* server) : ACommand(server, true) {}
Invite::~Invite() {}


// syntax: INVITE <nickname> <channel>
void Invite::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string target = args[0];
    std::string name = args[1];

    Channel* channel = _server->get_channel(name);
    if (!_is_valid_channel(client, channel, name))
        return;

    Client* dest = _server->get_client(target);
    if (!_is_valid_client(client, dest, channel, name))
        return;

    if (!_has_channel_privileges(client, channel))
        return;

    std::cout << "INVITE::Sending invite..." << std::endl;
    channel->add_to_inviteds(dest);
    ClientService::send_message(dest, RPL_INVITE(client->get_prefix(), target, name));
    std::cout << "SUCCEDED INVITE" << std::endl;
}


// Funções auxiliares

bool Invite::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    std::cout << "INVITE::Validate parameters..." << std::endl;
    if (args.size() == 2)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
    return false;
}
