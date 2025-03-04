#pragma once

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <vector>
# include <string>

# include "Server.hpp"

class Client;
class ACommand {
    protected:
        bool    _auth;
        Server  _server;

        ACommand();
        ACommand(const ACommand& src);
        
    public:
        ACommand(Server& server, bool auth = true);
        virtual ~ACommand();

        bool auth_required() const;

        virtual void execute(Client* client, std::vector<std::string> args) = 0;
};

#endif // COMMAND_HPP
