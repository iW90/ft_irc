#ifndef JOIN_HPP
# define JOIN_HPP

# include "ACommand.hpp"
# include "Client.hpp"
# include "ClientService.hpp"
# include "Macros.hpp"


class Join : public ACommand {
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

#endif // JOIN_HPP
