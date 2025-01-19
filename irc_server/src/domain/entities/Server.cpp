#include "Server.hpp"


Server::Server(const std::string& host, int port) {
    running = false;

    // Criando o socket (AF_INET para IPv4, SOCK_STREAM para TCP)
    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSocket == -1) {
        throw std::runtime_error("Erro ao criar o socket");
    }

    // Configurando o endereço do servidor
    address.sin_family = AF_INET;  // Família de endereço para IPv4
    address.sin_port = htons(port);  // Converte a porta para o formato de rede (big-endian)
    address.sin_addr.s_addr = inet_addr(host.c_str()); // Converte o endereço IP de string para formato binário
    
    if (address.sin_addr.s_addr == INADDR_NONE) {
        close(fdSocket);
        throw std::runtime_error("Endereço IP inválido ou erro na conversão");
    }
}

Server::~Server() {
    if (fdSocket != -1) {
        close(fdSocket);
    }
}


std::string Server::getHost() const {
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, ipStr, sizeof(ipStr));
    return std::string(ipStr);
}

void Server::setHost(const std::string& host) {
    if (inet_pton(AF_INET, host.c_str(), &address.sin_addr) <= 0) {
        throw std::runtime_error("Endereço IP inválido ou erro na conversão");
    }
}


int Server::getPort() const { return ntohs(address.sin_port); }
void Server::setPort(int port) { address.sin_port = htons(port); }

int Server::getSocket() const { return fdSocket; }
void Server::setSocket(int socket) { fdSocket = socket; }

bool Server::isRunning() const { return running; }
void Server::setRunning(bool running) { running = running;}

