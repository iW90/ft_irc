#include "ClientManager.hpp"

ClientManager::ClientManager(Poller& p) : poller(p) {}

ClientManager::~ClientManager() {}

void ClientManager::addClient(int socketFD, short events) {
    poller.addSocket(socketFD, events);
}

void ClientManager::removeClient(int socketFD) {
    poller.removeSocket(socketFD);
}
