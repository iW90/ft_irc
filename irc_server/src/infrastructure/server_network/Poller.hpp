#pragma once

#ifndef POLLER_HPP
# define POLLER_HPP

# include <vector>
# include <sys/epoll.h>
# include <stdexcept>
# include <iostream>
# include <unistd.h>
# include "irc_server/src/domain/Constants.hpp"


class Poller {
    private:
        int epoll_fd;  // Descritor do epoll
        int timeout;   // Timeout em milissegundos
        std::vector<struct epoll_event> fds;  // Lista de eventos monitorados

    public:
        Poller(int timeout_ms = POLLER_TIMEOUT);    // Construtor
        ~Poller();                                  // Destruidor

        int     pollClients();                              // Monitora os sockets
        void    addClient(int socketFD, short events);      // Adiciona um socket à lista de monitoramento
        void    removeClient(int socketFD);                 // Remove um socket da lista
        bool    isReadable(int socketFD);                   // Verifica se o socket está pronto para leitura
        bool    isWritable(int socketFD);                   // Verifica se o socket está pronto para escrita
        bool    isClosed(int socketFD);                     // Verifica se o socket foi fechado
        size_t  getClientCount() const;                     // Retorna o número de sockets monitorados
        struct epoll_event getClient(size_t index) const;   // Retorna o objeto epoll_event correspondente ao índice
};

#endif  // POLLER_HPP
