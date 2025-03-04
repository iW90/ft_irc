#ifndef QUIT_HPP
# define QUIT_HPP

# include "ACommand.hpp"
# include "ClientService.hpp"
# include "Macros.hpp"


class Quit : public ACommand {
    private:
        

    public:
        Quit(Server& server);
        ~Quit();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // QUIT_HPP
