#include "ServerManager.hpp"


ServerManager::ServerManager(Server& serv) : server(serv) {}

ServerManager::~ServerManager() {
    if (server.isRunning()) {
        stop();
    }
}

void ServerManager::start(const std::string& host, int port) {
    if (server.isRunning()) {
        std::cout << "Servidor já está rodando!" << std::endl;
        return;
    }

    try {
        configureSocket(host, port);
        bindSocket();
        listenForConnections();

        server.setRunning(true);
        std::cout << "Servidor iniciado e aguardando conexões..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao iniciar o servidor: " << e.what() << std::endl;
    }
}

void ServerManager::stop() {
    if (!server.isRunning()) {
        std::cout << "Servidor já está parado!" << std::endl;
        return;
    }

    try {
        closeSocket();
        server.setRunning(false);
        std::cout << "Servidor parado." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao parar o servidor: " << e.what() << std::endl;
    }
}


void ServerManager::configureSocket(const std::string& host, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw std::runtime_error("Erro ao criar o socket");
    }

    server.setSocket(sockfd);

    sockaddr_in address = server.getAddress();          // Configurações do server
    address.sin_port = htons(port);                     // Porta
    address.sin_addr.s_addr = inet_addr(host.c_str());  // Endereço IP

    if (address.sin_addr.s_addr == INADDR_NONE) {
        close(sockfd);
        server.setSocket(-1);
        throw std::runtime_error("Endereço IP inválido ou erro na conversão");
    }

    server.setAddress(address);
}

void ServerManager::bindSocket() {
    sockaddr_in address = server.getAddress();
    if (bind(server.getSocket(), (struct sockaddr*)&address, sizeof(address)) == -1) {
        throw std::runtime_error("Erro ao fazer bind do socket");
    }
}

void ServerManager::listenForConnections() {
    if (listen(server.getSocket(), 10) == -1) {
        throw std::runtime_error("Erro ao ouvir por conexões");
    }
}

void ServerManager::acceptConnection() {
    sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(server.getSocket(), (struct sockaddr*)&clientAddress, &clientAddrLen);
    if (clientSocket == -1) {
        throw std::runtime_error("Erro ao aceitar conexão");
    }

    std::cout << "Cliente conectado: " << inet_ntoa(clientAddress.sin_addr) << std::endl;
    close(clientSocket);  // Aqui você pode começar a interagir com o cliente
}

void ServerManager::setSocketNonBlocking() {
    int flags = fcntl(server.getSocket(), F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("Erro ao obter flags do socket");
    }

    if (fcntl(server.getSocket(), F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("Erro ao definir o socket como não bloqueante");
    }
}

void ServerManager::closeSocket() {
    if (close(server.getSocket()) == -1) {
        throw std::runtime_error("Erro ao fechar o socket");
    }
    std::cout << "Socket fechado com sucesso." << std::endl;
}
