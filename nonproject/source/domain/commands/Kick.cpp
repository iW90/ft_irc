#include "commands/Kick.hpp"


Kick::Kick(Server& server) : ACommand(server, true) {}
Kick::~Kick() {}


// syntax: KICK <channel> <client> :[<message>]
void Kick::execute(Client* client, std::vector<std::string> args) {
    // Verificar se os parâmetros são válidos
    if (!_has_valid_parameters(client, args)) return;

    // Extrair os dados necessários
    std::string name = args[0];
    std::string target = args[1];
    std::string reason = _extract_reason(args);

    // Verificar se o cliente está no canal e tem permissões suficientes
    Channel* channel = client->get_channel();
    if (!_is_valid_channel(client, channel, name))
        return;

    if (!_has_channel_privileges(client, channel))
        return;

    // Verificar se o destinatário está no canal
    Client* dest = _server.get_client(target);
    if (!_is_valid_recipient(client, dest, channel, name))
        return;

    // Executar o comando de kick
    ChannelService::kick_client(channel, client, dest, reason);
}

bool Kick::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
        return false;
    }
    return true;
}

std::string Kick::_extract_reason(const std::vector<std::string>& args) {
    if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1)) {
        std::string reason = "";
        for (size_t i = 2; i < args.size(); ++i) {
            reason.append(args[i]);
            reason.append(" ");
        }
        return reason;
    }
    return "No reason specified!";
}

bool Kick::_is_valid_channel(Client* client, Channel* channel, const std::string& name) {
    if (!channel || channel->get_name() != name) {
        ClientService::reply_message(client, ERR_NOTONCHANNEL(client->get_nickname(), name));
        return false;
    }
    return true;
}

bool Kick::_has_channel_privileges(Client* client, Channel* channel) {
    if (channel->get_admin() != client) {
        ClientService::reply_message(client, ERR_CHANOPRIVSNEEDED(client->get_nickname(), channel->get_name()));
        return false;
    }
    return true;
}

bool Kick::_is_valid_recipient(Client* client, Client* dest, Channel* channel, const std::string& name) {
    if (!dest) {
        ClientService::reply_message(client, ERR_NOSUCHNICK(client->get_nickname(), dest->get_nickname()));
        return false;
    }

    if (!dest->get_channel() || dest->get_channel() != channel) {
        ClientService::reply_message(client, ERR_USERNOTINCHANNEL(client->get_nickname(), dest->get_nickname(), name));
        return false;
    }
    
    return true;
}
