#include "commands/authentication/User.hpp"


User::User(Server& server) : ACommand(server, true) {}
User::~User() {}


// stntax: USER <username> <hostname> <servername> :<realname>
void    User::execute(Client* client, std::vector<std::string> args) {
    if (client->get_state() == REGISTERED) {
        ClientService::reply_message(client, ERR_ALREADYREGISTERED(client->get_nickname()));
        return;
    }

    if (args.size() < 4) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "USER"));
        return;
    }

    std::string realname = args[3];
    if (realname[0] == ':')
        realname = realname.substr(1);  // Remove o ':' se houver

    for (size_t i = 4; i < args.size(); ++i) // Concatena todos os nomes
        realname += " " + args[i];

    client->set_realname(realname);
    client->set_username(args[0]);

    if (client->get_state() != LOGGED_IN || client->get_nickname().empty())
		return;
    
    client->set_state(REGISTERED);
    ClientService::reply_message(client, RPL_WELCOME(client->get_nickname()));
}
