#include "Server.hpp"

Server::Server(IVault& vault, ISocket& socket, IMultiplexer& multiplexer) :
      _running(false),
      _vault(vault), 
      _socket(socket), 
      _multiplexer(multiplexer) {}

Server::~Server() {
    // Destruir todos os clients
    std::set<Client*>::iterator client_it;
    for (client_it = _clients.begin(); client_it != _clients.end(); ++client_it) {
        Client* client = *client_it;
        delete client;
    }
    _clients.clear();

    // Destruir todos os channels
    std::set<Channel*>::iterator channel_it;
    for (channel_it = _channels.begin(); channel_it != _channels.end(); ++channel_it) {
        Channel* channel = *channel_it;
        delete channel;
    }
    _channels.clear();

    // Destruir outros recursos
    delete &_vault;
    delete &_socket;
    delete &_multiplexer;
}


// Getters
const IVault& Server::get_vault() const { return _vault; }
const ISocket& Server::get_socket() const { return _socket; }
const IMultiplexer& Server::get_multiplexer() const { return _multiplexer; }
const std::set<Channel*>& Server::get_channels() const { return _channels; }
const std::set<Client*>& Server::get_clients() const { return _clients; }

Channel* Server::get_channel(const std::string& name) {
    for (std::set<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->get_name() == name)
            return *it;
    }
    return NULL; 
}



// Métodos
void Server::start() {
    try {
        _running = true;
        SignalManager::initialize(&_running);

        int total_events;

        std::cout << "Server is now running." << std::endl;

        _multiplexer.subscribe_fd_for_monitoring(_socket.get_fd());

        while(_running) {
            total_events = _multiplexer.check_for_events();
            _multiplexer.handle_events(total_events);
        }

    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn on the server.");
    }
}

void Server::stop() {
    try {
        if (_running) {
            _running = false;
            _multiplexer.unsubscribe_fd_for_monitoring(_socket.get_fd());
        }

        std::cout << "Server has been shut down." << std::endl;
    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn off the server.");
    }
}


Channel* Server::create_channel(const std::string& name, const std::string& key, Client* client) {
    Channel *channel = new Channel(name, key, client);
    _channels.insert(channel);

    return channel;
}
