#include "commands/server/Nick.hpp"


Nick::Nick(Server& server) : ACommand(server, false) {}
Nick::~Nick() {}


// syntax: NICK <nickname>
void    Nick::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string nickname = args[0];

    if (_is_nickname_taken(nickname, client))
        return;

    client->set_nickname(nickname);

    _set_client_state(client);
}


// Funções auxiliares

bool Nick::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() != 1) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "NICK"));
        return false;
    }
    return true;
}

bool Nick::_is_nickname_taken(const std::string& nickname, Client* client) {
    if (_server.get_client(nickname)) {
        ClientService::reply_message(client, ERR_NICKNAMEINUSE(client->get_nickname()));
        return true;
    }
    return false;
}

void Nick::_set_client_state(Client* client) {
    if (client->get_state() != LOGGED_IN || client->get_username().empty() || client->get_realname().empty())
        return;

    client->set_state(REGISTERED);
    ClientService::reply_message(client, RPL_WELCOME(client->get_nickname()));
}
