#include "ClientActionManager.hpp"

void ClientActionManager::send_message(Client* client, const std::string& message) {
    std::string buffer = message + "\r\n";
    if (send(client->get_fd(), buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}
