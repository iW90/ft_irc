#include "commands/authentication/Nick.hpp"


Nick::Nick(Server& server) : ACommand(server, true) {}
Nick::~Nick() {}


// syntax: NICK <nickname>
void    Nick::execute(Client* client, std::vector<std::string> args) {
    if (args.empty() || args[0].empty()) {
        ClientService::reply_message(client, ERR_NONICKNAMEGIVEN(client->get_nickname()));
        return;
    }

    std::string nickname = args[0];

    if (_server.get_client(nickname)) {
        ClientService::reply_message(client, ERR_NICKNAMEINUSE(client->get_nickname()));
        return;
    }

    client->set_nickname(nickname);

    if (client->get_state() != LOGGED_IN || \
        client->get_username().empty() || \
        client->get_realname().empty())
		return;
    
    client->set_state(REGISTERED);
    ClientService::reply_message(client, RPL_WELCOME(client->get_nickname()));
}
