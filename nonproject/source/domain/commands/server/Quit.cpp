#include "commands/server/Quit.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientService.hpp"
#include "ChannelService.hpp"
#include "IMultiplexer.hpp"
#include "Macros.hpp"
#include "Server.hpp"

Quit::Quit(Server* server) : ACommand(server, false) {}
Quit::~Quit() {}


// syntax: QUIT :<message>
void    Quit::execute(Client* client, std::vector<std::string> args) {
    std::string reason = args.empty() ? "Leaving server..." : args.at(0);

    if (reason.at(0) == ':')
        reason = reason.substr(1);

    ClientService::send_message(client, RPL_QUIT(client->get_prefix(), reason));
    IMultiplexer* multiplexer = _server->get_multiplexer();
    multiplexer->disconnect_client(client->get_fd());
}


// Funções auxiliares

bool Quit::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    (void)client;
    (void)args;
    return true;
}
