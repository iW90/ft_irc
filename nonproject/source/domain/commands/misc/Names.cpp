#include "commands/misc/Names.hpp"
#include "ClientService.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Macros.hpp"
#include "Server.hpp"


Names::Names(Server* server) : ACommand(server, false) {}
Names::~Names() {}


// syntax: NAMES #<channel>
void Names::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string channel_name = args[0];
    if (channel_name.at(0) != '#') {
        ClientService::send_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), channel_name));
        return;
    }

    channel_name.erase(0,1);
    Channel* channel = _server->get_channel(channel_name);
    if (channel != NULL) {
        ClientService::send_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), channel_name));
        return;
    }

    std::set<Client*> clients = channel->get_clients();
    for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        std::string user_info = (*it)->get_prefix();
        ClientService::send_message(client, RPL_NAMREPLY(client->get_nickname(), channel_name, user_info));
    }

    ClientService::send_message(client, RPL_ENDOFNAMES(client->get_nickname(), channel_name));
}

bool Names::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    std::cout << "NAMES::Validate parameters..." << std::endl;
    if (args.size() == 1)
        return true;
    ClientService::send_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "NAMES"));
    return false;
}
