#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <map>

#include "ACommand.hpp"


class CommandHandler {
    private:
        std::map<std::string, ACommand *>    _commands;

        std::string     _trim(const std::string& str);

    public:
        CommandHandler();
        ~CommandHandler();

        void    invoke(Client* client, const std::string& message);
};

#endif // COMMAND_HANDLER_HPP