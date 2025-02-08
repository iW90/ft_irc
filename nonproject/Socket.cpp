#include "Socket.hpp"

Socket::Socket(const std::string& host, int port) {
    _create_socket();
    _configure_socket();
    _set_non_blocking();
    _configure_address(host, port);
    _bind_socket_to_address();
}

Socket::~Socket() {
    if (_socket_fd != -1)
        ::close(_socket_fd); //::close() global, parte da unistd
}


// CRIA UM SOCKET EM UM FD
void Socket::_create_socket() {
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == -1)
        throw std::runtime_error("Erro ao criar o socket");
    /*
        - AF_INET indica que o socket usará endereços IPv4 para comunicação (AF_INET6: Para endereços IPv6).
        - SOCK_STREAM indica que o socket será do tipo orientado a conexão, ou seja, usará o protocolo TCP.
        - Quando o valor é 0, o sistema operacional escolhe automaticamente o protocolo padrão para o tipo 
        de socket especificado. No caso de SOCK_STREAM, o protocolo padrão é o TCP.
    */

}

// CONFIGURA OPÇÕES PARA SOCKET CRIADO
void Socket::_configure_socket() {
    int optval = 1; // 1 significa habilitar e 0 desabilitar
    if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        throw std::runtime_error("Error while setting socket options!");
    /*
        - SOL_SOCKET: Indica que a opção que está sendo configurada é uma opção de nível de socket.
        - SO_REUSEADDR: Especifica a opção que está sendo configurada. SO_REUSEADDR permite que o 
        endereço do socket seja reutilizado, o que é útil para evitar erros como "Address already 
        in use" quando você tenta reiniciar um servidor rapidamente.
        - &optval: Um ponteiro para o valor da opção, que é 1 (habilitado).
        - sizeof(optval): O tamanho do valor da opção, que é o tamanho de um int.
    */
}

// HABILITA O MODO NÃO BLOQUEANTE PARA O SOCKET
void Socket::_set_non_blocking() {
    if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
        throw std::runtime_error("Erro ao definir o socket como não bloqueante");
    /*
        - F_SETFL é uma flag que indica que estamos modificando os atributos do 
        arquivo/sockets. No caso, estamos definindo as flags do socket.
        - O_NONBLOCK é a flag que indica que o socket deve funcionar no modo não 
        bloqueante. Quando um socket está no modo bloqueante, operações como 
        read() ou write() podem fazer o programa esperar (bloquear) até que a 
        operação possa ser concluída. Com o modo não bloqueante, essas operações 
        retornam imediatamente, mesmo que não tenham sido concluídas, permitindo 
        que o programa continue executando outras tarefas enquanto aguarda os dados.
    */

}

// CONFIGURA O ENDEREÇO DO SOCKET
void Socket::_configure_address(const std::string& host, int port) {
    memset(&_address, 0, sizeof(_address));   // Limpa a estrutura sockaddr_in
    _address.sin_family = AF_INET;            // Define o tipo de família de endereço (default: IPv4)
    _address.sin_port = htons(port);          // Inicializa a porta (default: 6667)

    _address.sin_addr.s_addr = inet_addr(host.c_str()); // Define o IP (default: "127.0.0.1")
    if (_address.sin_addr.s_addr == INADDR_NONE)
        throw std::runtime_error("Endereço IP inválido ou erro na conversão");

    /*
        - htons() (host-to-network short) é usada para garantir que o valor da 
        porta seja convertido para a ordem de bytes correta para a rede, que
        é Big Endian.
        - inet_addr() converte um endereço IP em string (como "192.168.1.1") 
        para um formato binário, retornando INADDR_NONE quando o endereço é inválido.

        - Use "_address.sin_addr.s_addr = INADDR_ANY" se quiser usar um endereço
        qualquer disponível
    */
}

// ASSOCIA UM SOCKET A UM ENDEREÇO IP E A UMA PORTA
void Socket::_bind_socket_to_address() {
    if (::bind(_socket_fd, (struct sockaddr*)&_address, sizeof(_address)) == -1)
        throw std::runtime_error("Erro ao fazer bind do socket");
}
