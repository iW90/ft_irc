#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"
# include "ChannelService.hpp"


class Topic : public ACommand {
    private:
        bool        _has_valid_parameters(Client* client, const std::vector<std::string>& args);
        std::string _extract_topic(const std::vector<std::string>& args);
        bool        _has_channel_privileges(Client* client, Channel* channel);
        bool        _has_valid_channel(Client* client, Channel* channel);

    public:
        Topic(Server& server);
        ~Topic();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // TOPIC_HPP
