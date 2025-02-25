#include "ChannelManagement.hpp"

void ChannelManagement::broadcast(Channel* channel, const std::string& message) {
    std::vector<Client*>& clients = channel->get_clients();

    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        ClientActionManager::send_message(*it, message);
    }
}

void ChannelManagement::broadcast(Channel* channel, const std::string& message, Client* exclude) {
    std::vector<Client*>& clients = channel->get_clients();

    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (*it != exclude)
            ClientActionManager::send_message(*it, message);
    }
}

void ChannelManagement::add_client(Channel* channel, Client* client) {
    std::vector<Client*>& clients = channel->get_clients();
    clients.push_back(client);
}

void ChannelManagement::remove_client(Channel* channel, Client* client) {
    std::vector<Client*>& clients = channel->get_clients();
    
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (*it == client) {
            clients.erase(it);
            break;
        }
    }

    client->set_channel(NULL);

    // Se o cliente removido for o admin, atribui um novo admin
    if (client == channel->get_admin()) {
        if (!clients.empty()) {
            channel->set_admin(clients.front()); // Assume que sempre há um cliente restante
            broadcast(channel, client->get_nickname() + " is now the admin of the channel " + channel->get_name());
        }
    }
}

void ChannelManagement::kick_client(Channel* channel, Client* client, Client* target, const std::string& reason) {
    broadcast(channel, client->get_nickname() + " kicked " + target->get_nickname() + " from channel " + channel->get_name() + " for reason: " + reason);
    // validar se é admin para garantir que somente ele possa banir
    // criar uma lista de ban
    remove_client(channel, target);
}
