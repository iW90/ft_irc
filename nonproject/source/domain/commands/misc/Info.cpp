#include "commands/misc/Info.hpp"
#include "ClientService.hpp"
#include "Client.hpp"
#include "Macros.hpp"


Info::Info(Server* server) : ACommand(server, false) {}
Info::~Info() {}


// syntax: INFO
void Info::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    ClientService::send_message(client, RPL_INFO("ft_irc v1.0 by inwagner, maalexan and dfrade"));
    ClientService::send_message(client, RPL_ENDOFINFO());
}

bool Info::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    std::cout << "INFO::Validate parameters..." << std::endl;
    if (args.empty())
        return true;
    ClientService::send_message(client, ERR_NEEDMOREPARAMS(std::string("INFO")));
    return false;
}
