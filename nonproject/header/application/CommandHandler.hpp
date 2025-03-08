#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <map>

//# include "ACommand.hpp"
//# include "Macros.hpp"
//# include "ClientService.hpp"
//# include "Server.hpp"


class Server;
class Client;
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