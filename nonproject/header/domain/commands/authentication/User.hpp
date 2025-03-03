#ifndef USER_HPP
# define USER_HPP

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"


class User : public ACommand {
    private:
        

    public:
        User(Server& server);
        ~User();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // USER_HPP
