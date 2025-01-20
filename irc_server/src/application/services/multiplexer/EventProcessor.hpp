#ifndef MULTIPLEXER_HPP
# define MULTIPLEXER_HPP

# include "Poller.hpp"
# include <iostream>
# include <stdexcept>
# include <map>


class EventProcessor {
    private:
        bool    running;    // Flag para indicar se o multiplexer está em execução

        // Mapper para Event Handler
        typedef void (EventProcessor::*EventHandler)(int socketFD);
        std::map<int, EventHandler> eventHandlers;

        void handleReadable(int socketFD);
        void handleWritable(int socketFD);
        void handleClosed(int socketFD);

        // Funções auxiliares
        bool isRunning() const;
        void processPollResult(int ret);
        void processSocketEvents(int socketFD, uint32_t events);


    public:
        EventProcessor();
        ~EventProcessor();

        void handleEvents();                         // Lida com os eventos dos sockets
};

#endif  // MULTIPLEXER_HPP
