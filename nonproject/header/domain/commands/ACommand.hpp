#pragma once

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <vector>
# include <string>

# include "Macros.hpp"
# include "ChannelService.hpp"
# include "ClientService.hpp"


class Client;
class ACommand {
    protected:
        bool    _auth;
        Server  _server;

        virtual bool    _has_valid_parameters(Client* client, const std::vector<std::string>& args) = 0;

        bool            _is_valid_channel(Client* client, Channel* channel, const std::string& target);
        bool            _is_valid_client(Client* client, Client* dest, Channel* channel, const std::string& name);
        bool            _has_channel_privileges(Client* client, Channel* channel, const std::string& name);

        bool            _is_already_registered(Client* client);
        
    public:
        ACommand(Server& server, bool auth = true);
        virtual ~ACommand();

        bool auth_required() const;

        virtual void execute(Client* client, std::vector<std::string> args) = 0;
};

#endif // COMMAND_HPP
