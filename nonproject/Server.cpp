#include "Server.hpp"


Server::Server(const std::string& host, int port, const std::string& pass) : 
    Socket(host, port),
    _password(pass),
    _running(false) {}

Server::~Server() {}


// INICIA O SERVER
void Server::turn_on_server() {
    try {
        _running = true;

        _multiplexer.add_fd_to_multiplexer(Socket::_socket_fd);
        _multiplexer.handle_events(*this);

        std::cout << "Server is now running." << std::endl;
    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn on the server.");
    }
}

// INTERROMPE O SERVER
void Server::turn_off_server() {
    if (_running)
        _running = false;

    std::cout << "Server has been shut down." << std::endl;
}

// Getters
bool    Server::is_running() const { return _running; }
int     Server::get_server_fd() const { return Socket::_socket_fd; }
const   std::string Server::get_password() const { return _password; }