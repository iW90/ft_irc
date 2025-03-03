#include "commands/authentication/Pass.hpp"


Pass::Pass(Server& server) : ACommand(server, true) {}
Pass::~Pass() {}


// syntax: PASS :<password>
void    Pass::execute(Client* client, std::vector<std::string> args) {
    if (args.empty()) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "PASS"));
        return;
    }

    if (client->get_state() == REGISTERED) {
        ClientService::reply_message(client, ERR_ALREADYREGISTERED(client->get_nickname()));
        return;
    }

    std::string password = args[0].substr(args[0][0] == ':' ? 1 : 0);
    if (!_server.is_valid_pass(password)) {
        ClientService::reply_message(client, ERR_PASSWDMISMATCH(client->get_nickname()));
        return;
    }

    client->set_state(LOGGED_IN);
}
