#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "Poller.hpp"
#include <stdexcept>

class ClientManager {
    private:
        Poller& poller;  // Referência ao Poller

    public:
        ClientManager(Poller& p);

        // Adiciona um socket ao Poller
        void addClient(int socketFD, short events);

        // Remove um socket do Poller
        void removeClient(int socketFD);
};

#endif  // CLIENT_MANAGER_HPP
