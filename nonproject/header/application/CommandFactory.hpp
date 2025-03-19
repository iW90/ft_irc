#ifndef COMMAND_FACTORY_HPP
# define COMMAND_FACTORY_HPP

#include <string>

class Server;
class Client;


class CommandFactory {
  public:
    static void execute_command(Server* server, Client* client, const std::string& command);

};

#endif