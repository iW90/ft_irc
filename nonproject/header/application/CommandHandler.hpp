#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <map>

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"
# include "Server.hpp"

// # include "commands/server/Pass.hpp"
// # include "commands/server/Nick.hpp"
// # include "commands/server/User.hpp"
// # include "commands/server/Quit.hpp"
// # include "commands/operator/Invite.hpp"
// # include "commands/operator/Kick.hpp"
// # include "commands/operator/Mode.hpp"
// # include "commands/operator/Topic.hpp"
// # include "commands/operator/Invite.hpp"
// # include "commands/general/Join.hpp"
// # include "commands/general/Part.hpp"
// # include "commands/general/PrivMsg.hpp"


class Server;
class ACommand;
class CommandHandler {
    private:
        Server*                                 _server;
        std::map<std::string, ACommand *>       _commands;

        std::string     _trim(const std::string& str);

    public:
        CommandHandler(Server* server);
        ~CommandHandler();

        void    invoke(Client* client, const std::string& message);
};

#endif // COMMAND_HANDLER_HPP