class Server {
private:
    ConnectionManager connectionManager;
    EventHandler eventHandler;
    ClientManager clientManager;
    MessageProcessor messageProcessor;

public:
    void start(uint16_t port);
};


/*
void IRCServer::start(uint16_t port) {
    connectionManager.createListeningSocket(port);
    eventHandler.addSocket(connectionManager.getServerSocket(), EPOLLIN);

    while (true) {
        eventHandler.processEvents([this](int fd, uint32_t events) {
            if (fd == connectionManager.getServerSocket()) {
                int client_fd = connectionManager.acceptClient();
                clientManager.addClient(client_fd);
                eventHandler.addSocket(client_fd, EPOLLIN);
            } else if (events & EPOLLIN) {
                IRCClient* client = clientManager.getClient(fd);
                std::string message = client->receiveMessage();
                messageProcessor.processMessage(fd, message);
            }
        });
    }
}


*/