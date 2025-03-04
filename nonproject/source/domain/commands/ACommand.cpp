#include "commands/ACommand.hpp"

ACommand::ACommand(Server& server, bool auth) : _auth(auth), _server(server) {}

ACommand::~ACommand() {}

bool    ACommand::auth_required() const { return _auth; }
