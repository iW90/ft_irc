#ifndef JOIN_HPP
# define JOIN_HPP

# include "ACommand.hpp"


class Join : public ACommand {
    private:
        bool        _has_valid_parameters(Client* client, const std::vector<std::string>& args);
        bool        _is_already_in_channel(Client* client, std::string name);
        bool        _is_channel_full(Channel* channel, Client* client, const std::string& name);
        bool        _is_channel_key_valid(Channel* channel, Client* client, const std::string& pass, std::string name);
        Channel*    _get_or_create_channel(const std::string& name, const std::string& pass, Client* client);

    public:
        Join(Server* server);
        ~Join();

        void execute(Client* client, std::vector<std::string> args);
};

#endif // JOIN_HPP
