#include "Multiplexer.hpp"

Multiplexer::Multiplexer() {
    running = false;
}

Multiplexer::~Multiplexer() {}

void Multiplexer::start() {
    running = true;
    std::cout << "Multiplexer iniciado, aguardando eventos..." << std::endl;
}

void Multiplexer::stop() {
    running = false;
    std::cout << "Multiplexer parado." << std::endl;
}

void Multiplexer::addSocket(int socketFD, short events) {
    poller.addSocket(socketFD, events);
}

void Multiplexer::removeSocket(int socketFD) {
    poller.removeSocket(socketFD);
}

void Multiplexer::handleEvents() {
    if (!running) {
        std::cerr << "Multiplexer não está em execução!" << std::endl;
        return;
    }

    // Aguardar por eventos de sockets
    int ret = poller.pollSockets();
    if (ret < 0) {
        throw std::runtime_error("Erro ao executar poll");
    }
    else if (ret == 0) {
        std::cout << "Nenhum evento ocorrido no tempo de espera" << std::endl;
    }
    else {
        // Itera sobre os sockets monitorados e verifica os eventos
        for (size_t i = 0; i < poller.getSocketCount(); ++i) {
            int socketFD = poller.getSocket(i).fd;

            // Verifica se há dados para leitura
            if (poller.isReadable(socketFD)) {
                std::cout << "Dados disponíveis para leitura no socket " << socketFD << std::endl;
                // Adicione o código para ler dados
            }

            // Verifica se o socket está pronto para escrita
            if (poller.isWritable(socketFD)) {
                std::cout << "Socket " << socketFD << " pronto para escrita." << std::endl;
                // Adicione o código para escrever dados
            }

            // Verifica se o socket foi fechado
            if (poller.isClosed(socketFD)) {
                std::cout << "Socket " << socketFD << " foi fechado." << std::endl;
                // Adicione o código para fechar a conexão
            }
        }
    }
}
