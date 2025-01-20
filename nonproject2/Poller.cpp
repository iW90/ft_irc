#include "Poller.hpp"


Poller::Poller(int timeout_ms) {
    timeout = timeout_ms;
    epoll_fd = epoll_create1(0);  // Cria o descritor do epoll
    if (epoll_fd == -1)
        throw std::runtime_error("Erro ao criar epoll");
    fds.reserve(10); // Reserve um tamanho inicial para fds

    std::cout << "\n\nTESTE: " << fds.size() << "\n\n" << std::endl;
}



Poller::~Poller() {
    close(epoll_fd);  // Fecha o descritor do epoll
}

void Poller::addSocket(int socketFD, short events) {
    struct epoll_event ev;
    ev.events = 0;
    if (events & EPOLLIN) {
        ev.events |= EPOLLIN;  // Evento de leitura    (|= é um operador de atribuição bit a bit com OR (bitwise OR assignment))
    }
    if (events & EPOLLOUT) {
        ev.events |= EPOLLOUT; // Evento de escrita    (|= é um operador de atribuição bit a bit com OR (bitwise OR assignment))
    }
    ev.data.fd = socketFD;  // Associa o socket
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socketFD, &ev) == -1) {
        throw std::runtime_error("Erro ao adicionar socket ao epoll");
    }
}

void Poller::removeSocket(int socketFD) {
    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, socketFD, NULL) == -1) {
        throw std::runtime_error("Erro ao remover socket do epoll");
    }
}

int Poller::pollSockets() {
    std::vector<struct epoll_event> events(fds.size());    // Cria um array de epoll_event para aguardar eventos
    // int ret = epoll_wait(epoll_fd, &events[0], fds.size(), timeout);
    
    // Se o vetor fds estiver vazio, defina uma capacidade mínima (por exemplo, 10 eventos)
    size_t numEvents = fds.size();
    if (numEvents == 0)
        numEvents = 10;  // Número mínimo de eventos que você espera monitorar
    int ret = epoll_wait(epoll_fd, &events[0], numEvents, timeout);

    if (ret < 0)
        throw std::runtime_error("Erro ao executar epoll_wait");
    fds = events;  // Atualiza o vetor de eventos monitorados
    return ret;
}


bool Poller::isReadable(int socketFD) {
    for (size_t i = 0; i < fds.size(); ++i) {
        if (fds[i].data.fd == socketFD && (fds[i].events & EPOLLIN)) {
            return true;
        }
    }
    return false;
}

bool Poller::isWritable(int socketFD) {
    for (size_t i = 0; i < fds.size(); ++i) {
        if (fds[i].data.fd == socketFD && (fds[i].events & EPOLLOUT)) {
            return true;
        }
    }
    return false;
}

bool Poller::isClosed(int socketFD) {
    for (size_t i = 0; i < fds.size(); ++i) {
        if (fds[i].data.fd == socketFD && (fds[i].events & EPOLLHUP)) {
            return true;
        }
    }
    return false;
}

size_t Poller::getSocketCount() const {
    return fds.size();
}

struct epoll_event Poller::getSocket(size_t index) const {
    if (index >= fds.size()) {
        throw std::runtime_error("Índice fora dos limites");
    }
    return fds[index];
}
