#include "ServerService.hpp"


ServerService::ServerService(Server& serv) : server(serv) {}

ServerService::~ServerService() {
    if (server.isRunning()) {
        stop();
    }
}

void ServerService::start(const std::string& host, int port) {
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
        throw ServerException(e, "Erro ao iniciar o servidor");
    }
}

void ServerService::stop() {
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
        throw ServerException(e, "Erro ao parar o servidor");
    }
}


void ServerService::configureSocket(const std::string& host, int port) {
    try {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            throw std::runtime_error("Erro ao criar o socket");
        }

        server.setSocket(sockfd);

        // Configurando o endereço do servidor
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
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao configurar o socket");
    }
}

void ServerService::bindSocket() {
    try {
        sockaddr_in address = server.getAddress();
        if (bind(server.getSocket(), (struct sockaddr*)&address, sizeof(address)) == -1) {
            throw std::runtime_error("Erro ao fazer bind do socket");
        }
    }
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao fazer bind do socket");
    }
}

void ServerService::listenForConnections() {
    try {
        if (listen(server.getSocket(), 10) == -1) {
            throw std::runtime_error("Erro ao ouvir por conexões");
        }
    }
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao ouvir por conexões");
    }
}

void ServerService::acceptConnection() {
    try {
        sockaddr_in clientAddress;
        socklen_t clientAddrLen = sizeof(clientAddress);
        int clientSocket = accept(server.getSocket(), (struct sockaddr*)&clientAddress, &clientAddrLen);
        if (clientSocket == -1) {
            throw std::runtime_error("Erro ao aceitar conexão");
        }

        std::cout << "Cliente conectado: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

        // Aqui você pode começar a interagir com o cliente

        close(clientSocket);  
    }
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao aceitar conexão");
    } 
}

void ServerService::setSocketNonBlocking() {
    try {
        int flags = fcntl(server.getSocket(), F_GETFL, 0);
        if (flags == -1) {
            throw std::runtime_error("Erro ao obter flags do socket");
        }

        if (fcntl(server.getSocket(), F_SETFL, flags | O_NONBLOCK) == -1) {
            throw std::runtime_error("Erro ao definir o socket como não bloqueante");
        }
    }
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao definir socket como não bloqueante");
    }
}

void ServerService::closeSocket() {
    try {
        if (close(server.getSocket()) == -1) {
            throw std::runtime_error("Erro ao fechar o socket");
        }
        std::cout << "Socket fechado com sucesso." << std::endl;
    }
    catch (const std::exception& e) {
        throw ServerException(e, "Erro ao fechar o socket");
    }
}
