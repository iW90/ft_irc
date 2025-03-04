#include "commands/operator/Invite.hpp"


Invite::Invite(Server& server) : ACommand(server, true) {}
Invite::~Invite() {}


// syntax: INVITE <nickname> <channel>
void Invite::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string target = args[0];
    std::string name = args[1];

    Channel* channel = _server.get_channel(name);
    if (!_is_valid_channel(client, channel, name))
        return;

    Client* dest = _server.get_client(target);
    if (!_is_valid_client(client, dest, channel, name))
        return;

    if (!_has_channel_privileges(client, channel, name))
        return;

    channel->add_to_invited_clients(dest);

    ClientService::send_message(dest, RPL_INVITE(client->get_prefix(), target, name));
}


// Funções auxiliares

bool Invite::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() == 2)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
    return false;
}
