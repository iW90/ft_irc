#include <iostream>

#include "Vault.hpp"
#include "Socket.hpp"
#include "Multiplexer.hpp"
#include "Server.hpp"


int main() {
    const std::string IP_ADDRESS = "127.0.0.1";

    // Mock (serão informados como argumento)
    int         port = 6667;
    std::string password = "adminadmin123";

    // Injeções de dependência
    Vault       vault(password);
    Socket      server_socket(IP_ADDRESS, port);   
    Multiplexer multiplexer(server_socket.get_fd());

    Server      server(vault, server_socket, multiplexer);

    // Iniciando servidor
    server.start();

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


/* CONECTANDO AO SERVIDOR
nc 127.0.0.1 6667
Para desconectar, necessário o uso do ctrl+C.
*/