#include "commands/general/Quit.hpp"


Quit::Quit(Server& server) : ACommand(server, true) {}
Quit::~Quit() {}


// syntax: QUIT :<message>
void    Quit::execute(Client* client, std::vector<std::string> args) {
    std::string reason = args.empty() ? "Leaving server..." : args.at(0);

    if (reason.at(0) == ':')
        reason = reason.substr(1);

    ClientService::send_message(client, RPL_QUIT(client->get_prefix(), reason));
    IMultiplexer& multiplexer = _server.get_multiplexer();
    multiplexer.disconnect_client(client->get_fd());
}
