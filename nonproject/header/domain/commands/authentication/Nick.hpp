#ifndef NICK_HPP
# define NICK_HPP

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"


class Nick : public ACommand {
    private:
        

    public:
        Nick(Server& server);
        ~Nick();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // NICK_HPP
