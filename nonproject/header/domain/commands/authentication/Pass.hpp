#ifndef PASS_HPP
# define PASS_HPP

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"


class Pass : public ACommand {
    private:
        

    public:
        Pass(Server& server);
        ~Pass();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // PASS_HPP
