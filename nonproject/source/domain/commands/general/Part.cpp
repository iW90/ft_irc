#include "commands/general/Part.hpp"
#include "Server.hpp"
#include "ClientService.hpp"
#include "Macros.hpp"

Part::Part(Server* server) : ACommand(server, true) {}
Part::~Part() {}


// syntax: PART <channel> :<message>
void    Part::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string name = args[0];
    Channel     *channel = _server.get_channel(name);

    if (!_is_client_in_channel(client, channel, name))
        return;

    ClientService::leave_channel(client);
}


// Funções auxiliares

bool Part::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() > 0)
        return true;
    ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "PART"));
    return false;
}

bool Part::_is_client_in_channel(Client* client, Channel* channel, const std::string& name) {
    if (channel && client->get_channel() && client->get_channel()->get_name() == name)
        return true;

    ClientService::reply_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), name));
    return false;
}
