#include "CommandFactory.hpp"
#include "CommandHandler.hpp"


void CommandFactory::execute_command(Server* server, Client* client, const std::string& command) {
  CommandHandler handler(server);
  handler.handle_command(client, command);
}
