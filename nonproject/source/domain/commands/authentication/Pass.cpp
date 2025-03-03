#include "commands/authentication/Pass.hpp"


Pass::Pass(Server& server) : ACommand(server, true) {}
Pass::~Pass() {}


// syntax: PASS <password>
void    Pass::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    if (_is_already_registered(client))
        return;

    std::string password = args[0];
    if (!_is_password_valid(password)) {
        ClientService::reply_message(client, ERR_PASSWDMISMATCH(client->get_nickname()));
        return;
    }

    client->set_state(LOGGED_IN);
}


// Funções auxiliares

bool Pass::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() != 1) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "PASS"));
        return false;
    }
    return true;
}

bool Pass::_is_already_registered(Client* client) {
    if (client->get_state() == REGISTERED) {
        ClientService::reply_message(client, ERR_ALREADYREGISTERED(client->get_nickname()));
        return true;
    }
    return false;
}

bool Pass::_is_password_valid(const std::string& password) {
    return _server.is_valid_pass(password);
}
