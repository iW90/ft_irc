#include "Server.hpp"


Server::Server(int socket_fd, const std::string& pass, Multiplexer multiplexer) : 
    _fd(socket_fd),
    _running(false), 
    _password(pass),
    _multiplexer(multiplexer) {}

Server::~Server() {}


// INICIA O SERVER
void Server::turn_on() {
    try {
        int total_events;
        _running = true;
        std::cout << "Server is now running." << std::endl;

        _multiplexer.subscribe_fd_for_monitoring(_fd);

        while(_running) {
            total_events = _multiplexer.check_for_events();
            _multiplexer.handle_events(total_events);
        }

    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn on the server.");
    }
}

// INTERROMPE O SERVER
void Server::turn_off() {
    try {
        if (_running) {
            _running = false;
            _multiplexer.unsubscribe_fd_for_monitoring(_fd);
        }

        std::cout << "Server has been shut down." << std::endl;
    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn off the server.");
    }
}

// Getters
bool    Server::is_running() const { return _running; }
const   std::string Server::get_password() const { return _password; }