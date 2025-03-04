#ifndef PRIV_MSG_HPP
# define PRIV_MSG_HPP

# include "ACommand.hpp"
# include "ClientService.hpp"
# include "Channel.hpp"
# include "Macros.hpp"


class PrivMsg : public ACommand {
    private:
        bool        _has_valid_parameters(Client* client, const std::vector<std::string>& args);
        std::string _build_message(const std::vector<std::string>& args);
        void        _handle_channel_message(Client* client, const std::string& target, const std::string& message);
        bool        _is_channel_valid(Client* client, const std::string& target, Channel* channel);
        bool        _is_channel_accessible(Client* client, Channel* channel);
        void        _handle_client_message(Client* client, const std::string& target, const std::string& message);

    public:
        PrivMsg(Server& server);
        ~PrivMsg();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // PRIV_MSG_HPP
