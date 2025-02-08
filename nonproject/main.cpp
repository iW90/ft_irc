#include <iostream>
#include "Server.hpp"

int main() {
    // Cria uma instância de servidor e socket
    Server server("127.0.0.1", 6667, "123");
    server.turn_on();

    std::cout << "Servidor iniciado. Pressione ENTER para parar o servidor..." << std::endl;
    // std::cin.get();  // Espera o usuário pressionar ENTER

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