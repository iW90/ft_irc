#ifndef KICK_HPP
# define KICK_HPP

# include "ACommand.hpp"
# include "Macros.hpp"
# include "ClientService.hpp"
# include "ChannelService.hpp"


class Kick : public ACommand {
    private:
        bool _has_valid_parameters(Client* client, const std::vector<std::string>& args);
        std::string _extract_reason(const std::vector<std::string>& args);
        bool _is_valid_channel(Client* client, Channel* channel, const std::string& name);
        bool _has_channel_privileges(Client* client, Channel* channel);
        bool _is_valid_recipient(Client* client, Client* dest, Channel* channel, const std::string& name);

    public:
        Kick(Server& server);
        ~Kick();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // KICK_HPP
