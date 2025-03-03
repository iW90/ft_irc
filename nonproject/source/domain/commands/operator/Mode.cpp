#include "commands/operator/Mode.hpp"


Mode::Mode(Server& server) : ACommand(server, true) {}
Mode::~Mode() {}


// syntax:  MODE <nickname> <flags>
//          MODE <channel> <flags> <args>
void Mode::execute(Client* client, std::vector<std::string> args) {
    if (!_has_valid_parameters(client, args))
        return;

    std::string target = args.at(0);
    Channel* channel = _server.get_channel(target);
    if (!_has_valid_channel(client, channel, target))
        return;

    // Verifica as permissões do canal
    if (!_has_channel_privileges(client, channel, target))
        return;

    // Processa os modos
    _process_modes(client, args, channel);
}


bool Mode::_has_valid_parameters(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        ClientService::reply_message(client, ERR_NEEDMOREPARAMS(client->get_nickname(), "MODE"));
        return false;
    }
    return true;
}

bool Mode::_has_valid_channel(Client* client, Channel* channel, const std::string& target) {
    if (!channel) {
        ClientService::reply_message(client, ERR_NOSUCHCHANNEL(client->get_nickname(), target));
        return false;
    }
    return true;
}

bool Mode::_has_channel_privileges(Client* client, Channel* channel, const std::string& target) {
    if (channel->get_admin() != client) {
        ClientService::reply_message(client, ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
        return false;
    }
    return true;
}

void Mode::_process_modes(Client* client, std::vector<std::string> args, Channel* channel) {
    int i = 0, p = 2;
    char c;

    while ((c = args[1][i])) {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';

        switch (c) {
            case 'n':
                _set_mode_n(client, channel, active);
                break;
            case 'l':
                _set_mode_l(client, channel, active, args, p);
                break;
            case 'k':
                _set_mode_k(client, channel, active, args, p);
                break;
            default:
                break;
        }
        i++;
    }
}

// Modes
void Mode::_set_mode_n(Client* client, Channel* channel, bool active) {
    channel->set_external_messages_allowed(active);
    ChannelService::broadcast(channel, RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+n" : "-n"), ""));
}

void Mode::_set_mode_l(Client* client, Channel* channel, bool active, std::vector<std::string>& args, int& p) {
    channel->set_limit(active ? atoi(args[p].c_str()) : 0);
    ChannelService::broadcast(channel, RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
    p += active ? 1 : 0;
}

void Mode::_set_mode_k(Client* client, Channel* channel, bool active, std::vector<std::string>& args, int& p) {
    channel->set_key(active ? args[p] : "");
    ChannelService::broadcast(channel, RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
    p += active ? 1 : 0;
}
