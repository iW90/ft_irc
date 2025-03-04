#include "commands/server/Pass.hpp"


Pass::Pass(Server& server) : ACommand(server, false) {}
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
    if (args.size() == 1)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "PASS"));
    return false;
}


bool Pass::_is_password_valid(const std::string& password) {
    return _server.is_valid_pass(password);
}
