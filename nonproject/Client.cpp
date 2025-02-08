#include "Client.hpp"

Client::Client(int fd, const std::string& host, int port) {
    _fd = fd;

    memset(&_address, 0, sizeof(_address));   // Limpa a estrutura sockaddr_in
    _address.sin_family = AF_INET;            // Define o tipo de família de endereço (default: IPv4)
    _address.sin_port = htons(port);          // Inicializa a porta

    _address.sin_addr.s_addr = inet_addr(host.c_str()); // Define o IP do client
    if (_address.sin_addr.s_addr == INADDR_NONE)
        throw std::runtime_error("Error while converting or invalid address");
}

Client::~Client() {}