#include "EventProcessor.hpp"

EventProcessor::EventProcessor() {


    // Associa eventos a funções de tratamento no construtor
    eventHandlers[EPOLLIN] = &EventProcessor::handleReadable;
    eventHandlers[EPOLLOUT] = &EventProcessor::handleWritable;
    eventHandlers[EPOLLHUP] = &EventProcessor::handleClosed;
}

EventProcessor::~EventProcessor() {}



void EventProcessor::processPollResult(int ret) {
    if (ret < 0) {
        throw std::runtime_error("Erro ao executar epoll_wait");
    } else if (ret == 0) {
        std::cout << "Nenhum evento ocorrido no tempo de espera" << std::endl;
    }
}

void EventProcessor::processSocketEvents(int socketFD, uint32_t events) {
    for (std::map<int, EventHandler>::iterator it = eventHandlers.begin(); it != eventHandlers.end(); ++it) {
        if (events & it->first) {
            (this->*(it->second))(socketFD);
        }
    }
}

void EventProcessor::handleEvents() {
    if (!isRunning())
        return;

    int ret = poller.pollSockets();
    processPollResult(ret);

    for (size_t i = 0; i < poller.getSocketCount(); ++i) {
        int socketFD = poller.getSocket(i).data.fd;
        uint32_t events = poller.getSocket(i).events;
        processSocketEvents(socketFD, events);
    }
}

void EventProcessor::handleReadable(int socketFD) {
    std::cout << "Dados disponíveis para leitura no socket " << socketFD << std::endl;
    // Adicione aqui o código para ler dados
}

void EventProcessor::handleWritable(int socketFD) {
    std::cout << "Socket " << socketFD << " pronto para escrita." << std::endl;
    // Adicione aqui o código para escrever dados
}

void EventProcessor::handleClosed(int socketFD) {
    std::cout << "Socket " << socketFD << " foi fechado." << std::endl;
    // Adicione aqui o código para fechar a conexão
}
