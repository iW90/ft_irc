#include <iostream>

#include "Vault.hpp"
#include "Socket.hpp"
#include "Multiplexer.hpp"
#include "ServerException.hpp"


void turn_off(bool& running, Multiplexer& multiplexer, int server_fd) {
    try {
        if (running) {
            running = false;
            multiplexer.unsubscribe_fd_for_monitoring(server_fd);
        }

        std::cout << "Server has been shut down." << std::endl;
    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn off the server.");
    }
}

void turn_on(bool& running, Multiplexer& multiplexer, int server_fd) {
    try {
        int total_events;
        running = true;
        std::cout << "Server is now running." << std::endl;

        multiplexer.subscribe_fd_for_monitoring(server_fd);

        while(running) {
            total_events = multiplexer.check_for_events();
            multiplexer.handle_events(total_events);
        }

    } catch (const std::exception& e) {
        throw ServerException(e, "Unable to turn on the server.");
    }
}


int main() {
    bool        running = false;
    std::string ip_address = "127.0.0.1";

    // Mock (serão informados como argumento)
    int         port = 6667;
    std::string password = "adminadmin123";

    // Instância do cofre
    Vault       vault(password);

    // Instância do socket do servidor
    Socket      server_socket(ip_address, port);
    int         server_fd = server_socket.get_fd();

    // Instância do multiplexador    
    Multiplexer multiplexer(server_fd);

    // Iniciando servidor
    turn_on(running, multiplexer, server_fd);



    return 0;
}


/* TESTANDO CONNECTIVIDADE
nc -zv 127.0.0.1 6667
Se o servidor estiver ativo e aceitando conexões, aparece "Ncat: Connected to 127.0.0.1:6667".
Caso contrário, verá uma mensagem de erro, "Ncat: Connection refused."

ou

netstat -tuln | grep 6667
Se o servidor estiver rodando, o comando retornará uma linha mostrando que ele está escutando na porta 6667.
Se não houver saída, o servidor não está rodando ou não está escutando na porta especificada.
*/