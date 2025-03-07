#include "commands/operator/Kick.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientService.hpp"
#include "ChannelService.hpp"
#include "Macros.hpp"
#include "Server.hpp"

Kick::Kick(Server* server) : ACommand(server, true) {}
Kick::~Kick() {}


// syntax: KICK <channel> <client> :<message>
void Kick::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string name = args[0];
    std::string target = args[1];
    std::string reason = _extract_reason(args);

    Channel* channel = client->get_channel();
    if (!_is_valid_channel(client, channel, name))
        return;

    if (!_has_channel_privileges(client, channel))
        return;

    Client* dest = _server->get_client(target);
    if (!_is_valid_client(client, dest, channel, name))
        return;

    ChannelService::kick_client(channel, client, dest, reason);
}


// Funções auxiliares

bool Kick::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() > 1)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
    return false;
}

std::string Kick::_extract_reason(const std::vector<std::string>& args) {
    if (!(args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1)))
        return "No reason specified!";

    std::string reason = "";
    for (size_t i = 2; i < args.size(); ++i) {
        reason.append(args[i]);
        reason.append(" ");
    }
    return reason;
}
