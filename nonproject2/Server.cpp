#include "Server.hpp"


Server::Server() : running(false) {
    memset(&address, 0, sizeof(address));   // Zera a estrutura sockaddr_in
    address.sin_family = AF_INET;           // Define o tipo de família de endereço (IPv4)
    address.sin_port = 0;                   // Inicializa a porta com valor 0 (pode ser alterado depois)
    address.sin_addr.s_addr = INADDR_ANY;   // Define o IP como INADDR_ANY (qualquer endereço disponível)
}

Server::~Server() {}

struct sockaddr_in Server::getAddress() const {
    return address;
}

void Server::setAddress(const struct sockaddr_in& addr) {
    address = addr;
}

bool Server::isRunning() const {
    return running;
}

void Server::setRunning(bool runn) {
    running = runn;
}
