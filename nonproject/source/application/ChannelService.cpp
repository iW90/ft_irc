#include "ChannelService.hpp"


void ChannelService::broadcast(Channel* channel, const std::string& message, Client* exclude) {
    std::set<Client*>& clients = channel->get_clients();

    for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (*it != exclude)
            ClientService::send_message(*it, message);
    }
}

/* O Client só será adicionado ao canal se:
    - Não estiver na black list, ou;
    - Tiver valor menor que três na black list.
*/
int ChannelService::add_client(Channel* channel, Client* client) {
    std::map<Client*, int>& black_list = channel->get_black_list();
    std::map<Client*, int>::iterator it = black_list.find(client);

    if (it == black_list.end() || it->second < MAX_BLACKLIST_VIOLATIONS) {
        channel->add_to_clients(client);

        std::string nicknameClient = client->get_nickname();
        std::string channelName = channel->get_name();
        std::string joinMessage = " joined the channel " + channelName;
        broadcast(channel, nicknameClient + joinMessage);

        return 0;
    }

    return -1;
}

void ChannelService::remove_client(Channel* channel, Client* client) {
    std::set<Client*>& clients = channel->get_clients();
    std::set<Client*>::iterator it = clients.find(client);
    if (it != clients.end())
        clients.erase(it);

    _change_admin_if_needed(channel, client);

    std::string nicknameClient = client->get_nickname();
    std::string channelName = channel->get_name();
    std::string leaveMessage = " left " + nicknameClient + " from channel " + channelName;
    broadcast(channel, nicknameClient + leaveMessage);
}

void ChannelService::kick_client(Channel* channel, Client* client, Client* target, const std::string& reason) {
    if (channel->get_admin() != client)
        return ;

    channel->add_to_black_list(target);
    remove_client(channel, target);
    target->set_channel(NULL);


    std::string nicknameClient = client->get_nickname();
    std::string nicknameTarget = target->get_nickname();
    std::string channelName = channel->get_name();
    std::string kickMessage = " kicked " + nicknameTarget + " from channel " + channelName + " for reason: " + reason;
    broadcast(channel, nicknameClient + kickMessage);
}

void ChannelService::_change_admin_if_needed(Channel* channel, Client* client) {
    if (client != channel->get_admin())
        return ;

    std::set<Client*>& clients = channel->get_clients();

    if (!clients.empty()) {
        std::set<Client*>::iterator it = clients.begin();
        channel->set_admin(*it);

        std::string nicknameClient = client->get_nickname();
        std::string channelName = channel->get_name();
        std::string adminMessage = " is now the admin of the channel " + channelName;
        broadcast(channel, nicknameClient + adminMessage);
    }
}
