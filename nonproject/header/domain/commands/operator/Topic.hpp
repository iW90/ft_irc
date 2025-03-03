#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "ACommand.hpp"


class Topic : public ACommand {
    private:
        

    public:
        Topic(Server& server);
        ~Topic();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // TOPIC_HPP
