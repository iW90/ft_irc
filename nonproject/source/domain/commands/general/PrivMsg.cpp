#include "commands/general/PrivMsg.hpp"


PrivMsg::PrivMsg(Server& server) : ACommand(server, true) {}
PrivMsg::~PrivMsg() {}


// syntax: PRIVMSG <msgtarget> :<message>
void PrivMsg::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string target = args.at(0);
    std::string message = _build_message(args);

    if (target.at(0) == '#')
        _handle_channel_message(client, target, message);
    else
        _handle_client_message(client, target, message);
}


// Funções auxiliares

bool PrivMsg::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 2 || args[0].empty() || args[1].empty()) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "PRIVMSG"));
        return false;
    }
    return true;
}

std::string PrivMsg::_build_message(const std::vector<std::string>& args) {
    std::string message;
    for (std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); ++it)
        message.append(*it + " ");

    if (message.at(0) == ':')
        message = message.substr(1);

    return message;
}

void PrivMsg::_handle_channel_message(Client* client, const std::string& target, const std::string& message) {
    Channel* channel = client->get_channel();

    if (!_is_valid_channel(client, channel, target))
        return;

    if (!_is_channel_accessible(client, channel))
        return;

    ChannelService::broadcast(channel, RPL_PRIVMSG(client->get_prefix(), target, message), client);
}

bool PrivMsg::_is_channel_accessible(Client* client, Channel* channel) {
    if (!channel->is_external_messages_allowed()) {
        std::vector<std::string> nicknames = channel->get_nicknames();

        std::vector<std::string>::iterator it = std::find(nicknames.begin(), nicknames.end(), client->get_nickname());

        if (it == nicknames.end()) {
            ClientService::reply_message(client, ERR_CANNOTSENDTOCHAN(client->get_nickname(), channel->get_name()));
            return false;
        }
    }
    return true;
}

void PrivMsg::_handle_client_message(Client* client, const std::string& target, const std::string& message) {
    Client* dest = _server.get_client(target);
    if (!dest) {
        ClientService::reply_message(client, ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }

    ClientService::send_message(dest, RPL_PRIVMSG(client->get_prefix(), target, message));
}
