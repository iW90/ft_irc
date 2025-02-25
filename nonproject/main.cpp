#include <iostream>
#include "Server.hpp"

int main() {
    int         port = 6667;
    std::string ip_address = "127.0.0.1";
    Socket      server_socket(ip_address, port);
    int         server_fd = server_socket.get_fd();
    
    Multiplexer multiplexer(server_fd);
    int         multiplexer_fd = multiplexer.get_epoll_fd();

    std::string password = "123";
    Server      server(server_fd, password, multiplexer);







    server.turn_on();

    (void)multiplexer_fd;







    server.turn_off();


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