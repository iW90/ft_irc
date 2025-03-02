#ifndef IRC_JOIN_HPP
# define IRC_JOIN_HPP

# include "ACommand.hpp"
# include "Client.hpp"
# include "ClientService.hpp"

#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"
#define ERR_TOOMANYCHANNELS(source, channel)            "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"

class Join : public ACommand
{
    private:
        bool        _is_already_in_channel(Client* client);
        bool        _is_channel_full(Channel* channel);
        bool        _is_channel_key_valid(Channel* channel, const std::string& pass);
        Channel*    _get_or_create_channel(const std::string& name, const std::string& pass, Client* client);

    public:

        Join(Server& server);
        ~Join();

        void execute(Client* client, std::vector<std::string> args);
};

#endif
