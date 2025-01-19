#ifndef MULTIPLEXER_HPP
# define MULTIPLEXER_HPP

# include "Poller.hpp"
# include <iostream>
# include <stdexcept>
# include <map>


class Multiplexer {
    private:
        Poller  poller;     // Objeto Poller para gerenciar os sockets
        bool    running;    // Flag para indicar se o multiplexer está em execução

        // Mapper para Event Handler
        typedef void (Multiplexer::*EventHandler)(int socketFD);
        std::map<short, EventHandler> eventHandlers;

        void handleReadable(int socketFD);
        void handleWritable(int socketFD);
        void handleClosed(int socketFD);

        // Funções auxiliares
        bool isRunning() const;
        void processPollResult(int ret);
        void processSocketEvents(int socketFD, uint32_t events);


    public:
        Multiplexer();
        ~Multiplexer();

        void start();   // Inicia o multiplexer e começa a escutar eventos
        void stop();    // Para o multiplexer

        void addSocket(int socketFD, short events);  // Adiciona um socket ao multiplexer
        void removeSocket(int socketFD);             // Remove um socket do multiplexer
        void handleEvents();                         // Lida com os eventos dos sockets
};

#endif  // MULTIPLEXER_HPP
