#include "commands/ACommand.hpp"


ACommand::ACommand(Server& server, bool auth) : _auth(auth), _server(server) {}

ACommand::~ACommand() {}


bool    ACommand::auth_required() const { return _auth; }


// Funções auxiliares

bool ACommand::_is_on_channel(Client* client, Channel* channel, const std::string& name) {
    if (channel == client->get_channel())
        return true;
    ClientService::reply_message(client, ERR_NOTONCHANNEL(client->get_nickname(), name));
    return false;
}

bool ACommand::_has_channel_privileges(Client* client, Channel* channel) {
    Client* admin = channel->get_admin();
    if (client != admin && (channel->get_operators().first && !channel->get_operator(client))) {
        ClientService::reply_message(client, ERR_NOPRIVILEGES(client->get_nickname()));
        return false;
    }
    return true;
}

bool ACommand::_is_already_registered(Client* client) {
    if (client->get_state() != REGISTERED)
        return false;
    ClientService::reply_message(client, ERR_ALREADYREGISTERED(client->get_nickname()));
    return true;
}

bool ACommand::_is_valid_channel(Client* client, Channel* channel, const std::string& target) {
    if (channel)
        return true;
    ClientService::reply_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), target));
    return false;
}

bool ACommand::_is_valid_client(Client* client, Client* dest, Channel* channel, const std::string& name) {
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
