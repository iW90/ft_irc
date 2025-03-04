#include "Server.hpp"

Server::Server(IVault& vault, ISocket& socket, IMultiplexer& multiplexer) :
      _running(false),
      _vault(vault), 
      _socket(socket), 
      _multiplexer(multiplexer) {}

Server::~Server() {
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
// const IVault& Server::get_vault() const { return _vault; }
// const ISocket& Server::get_socket() const { return _socket; }
IMultiplexer&                   Server::get_multiplexer() const { return _multiplexer; }
const std::set<Channel*>&       Server::get_channels() const { return _channels; }
const std::map<int, Client*>&   Server::get_clients() const { return _multiplexer.get_clients(); }

Channel* Server::get_channel(const std::string& name) {
    for (std::set<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->get_name() == name)
            return *it;
    }
    return NULL; 
}


Client* Server::get_client(const std::string& target) {
    return _multiplexer.get_client(target);
}

// Setters
void Server::set_command_handler(CommandHandler* handler) { _command_handler = handler; }

// Métodos
void Server::start() {
    try {
        _running = true;
        SignalManager::initialize(&_running);

        CommandHandler handler = CommandHandler(this);
        set_command_handler(&handler);

        int total_events;

        std::cout << "Server is now running." << std::endl;

        _multiplexer.subscribe_fd_for_monitoring(_socket.get_fd());

        while(_running) {
            total_events = _multiplexer.check_for_events();
            _multiplexer.handle_events(total_events, &handler);
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
    (void)key;
    Channel* channel = new Channel(client, name);
    _channels.insert(channel);

    return channel;
}

bool Server::is_valid_pass(std::string pass) {
    return _vault.validate_password(pass);
}
