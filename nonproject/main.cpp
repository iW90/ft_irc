#include <iostream>
#include "Server.hpp"

int main() {
    std::string ip_address = "127.0.0.1";
    std::string password = "123";
    int         port = 6667;
    Server      server(ip_address, port, password);
    
    int         server_fd = server.get_server_fd();
    Multiplexer multiplexer(server_fd);
    int         multiplexer_fd = multiplexer.get_epoll_fd();

    server.turn_on(multiplexer);









    server.turn_off(multiplexer);


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