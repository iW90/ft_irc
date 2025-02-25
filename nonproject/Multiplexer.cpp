#include "Multiplexer.hpp"


Multiplexer::Multiplexer(int server_fd) {
    _server_fd = server_fd;
    _epoll_fd = epoll_create1(0);
    if (_epoll_fd == -1)
        throw std::runtime_error("Failed to create epoll file descriptor");

    /*
        int epoll_create1(int size);
        - size: O número máximo de descritores de arquivo que você espera monitorar
            (no Linux, pode ser ignorado, mas deve ser fornecido).
        - Retorna um fd para o "monitor" de epoll. Se falhar, retorna -1.
    */
}

Multiplexer::~Multiplexer() {
    if (_epoll_fd != -1)
        ::close(_epoll_fd);
}

int Multiplexer::get_epoll_fd() const { return _epoll_fd; }

// ADICIONA UM NOVO FD PARA SER MONITORADO
void Multiplexer::subscribe_fd_for_monitoring(int fd) {
    epoll_event event;

    event.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP;
    event.data.fd = fd;
    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1)
        throw std::runtime_error("Failed to add fd to epoll");

    /*
        EPOLLIN
        - Conexões de clientes:
            No início, você está interessado em saber quando um cliente tenta 
            se conectar ao servidor (quando o socket de servidor tem uma 
            solicitação de conexão pendente). Nesse caso, você usaria EPOLLIN, 
            que indicaria que o servidor deve chamar accept() para aceitar a 
            conexão do cliente.
        - Mensagens de clientes já conectados:
            Depois que um cliente se conecta ao servidor e você aceita a conexão, 
            o socket do cliente precisa ser monitorado para ler mensagens 
            enviadas por esse cliente. Isso também requer o uso de EPOLLIN, porque 
            você está interessado em dados que o cliente envia ao servidor.

        - epoll_event é uma struct que descreve o que você quer monitorar 
            para o socket em questão. Ele contém o atributo "events" para o tipo
            de evento que quer monitorar (EPOLLIN, EPOLLOUT, EPOLLERR, etc.) e
            "data" onde são armazenados dados associados ao fd (como o ID do socket).
        - epoll_ctl é usada para modificar o conjunto de arquivos monitorados 
            pelo epoll_fd.
        - EPOLL_CTL_ADD especifica que estamos adicionando um novo fd (socket)
            para ser monitorado.
    */
}

// REMOVE UM FD DO MONITORAMENTO
void Multiplexer::unsubscribe_fd_for_monitoring(int fd) {
    if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL) < 0)
        throw std::runtime_error("Error while removing client fd from epoll");

    /*
        - EPOLL_CTL_DEL especifica que estamos removendo um fd (socket)
            da lista de eventos monitorados.
    */
}

// LOOPING QUE FICA MONITORANDO EVENTOS
int Multiplexer::check_for_events() {

    int total_events = epoll_wait(_epoll_fd, _events, MAX_EVENTS, -1); //implementar o sinal de sair do programa
    if (total_events == -1)
        throw std::runtime_error("Error while polling with epoll");

    return total_events;

    /*
        - epoll_wait é uma função que bloqueia o thread até que um evento 
            ocorra em um dos fds monitorados pelo epoll.
        - _events: Um array onde os eventos que ocorreram serão armazenados. 
            A função preencherá esse array com informações sobre os descritores 
            de arquivos que estão prontos para serem lidos/escritos.
        - MAX_EVENTS: Número máximo de eventos que podem ser retornados 
            na chamada de epoll_wait. Caso ultrapasse, o evento será perdido.
        - timeout (-1): Valor para bloqueio indefinido (espera até que pelo 
            menos um evento aconteça). Ou seja, o servidor vai "esperar" sem 
            fazer nada até que um evento relevante (como dados para ler, uma 
            nova conexão, etc.) ocorra em um dos fds monitorados. 
    */

}

// PARSER PARA GERENCIAR OS DIFERENTES EVENTOS
void Multiplexer::handle_events(int total_events) {
    for (int i = 0; i < total_events; i++) {

        // Eventos do servidor
        if (_events[i].data.fd == _server_fd) {
            // Nova conexão (novo client tentando conectar)
            if (_events[i].events & EPOLLIN)
                connect_client(_events[i].data.fd);


        // Eventos do client
        } else {
            // Se o evento for de desconexão ou erro do client
            if ((_events[i].events & (EPOLLHUP | EPOLLERR)))
                disconnect_client(_events[i].data.fd);

            if (_events[i].events & EPOLLIN)
                read_client_message(_events[i].data.fd);

        }
    }
}

// DISCONECTA O CLIENT DO SERVER
void Multiplexer::disconnect_client(int client_fd) {
    unsubscribe_fd_for_monitoring(client_fd);
    ::close(client_fd);
    std::cout << "Client disconnected." << std::endl;
}

// CONECTA UM CLIENT AO SERVER
int Multiplexer::connect_client(int server_fd) {
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    int client_fd = ::accept(server_fd, (sockaddr*)&addr, &size);
    if (client_fd == -1)
        throw std::runtime_error("Error to accept connection");

    subscribe_fd_for_monitoring(client_fd);
    std::cout << "Client connected." << std::endl;

    return client_fd;

    /*
        int ::accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        - sockfd é o socket do servidor.
        - addr é um ponteiro para uma estrutura sockaddr onde as informações 
            sobre o endereço do cliente serão armazenadas (como o IP e a 
            porta de onde a conexão foi feita).
        - addrlen é um ponteiro para a variável que contém o tamanho da 
            estrutura sockaddr. Quando accept() for bem-sucedido, ele 
            preencherá essa estrutura com o endereço do cliente.
        - retorna o fd do client.
    */    
}

// MINI GNL
void Multiplexer::read_client_message(int client_fd) {
    try {
        std::string message;
        
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);

        // Vai salvando a mensagem no buffer, e depois agrega em "message"
        while (!strstr(buffer, "\n"))
        {
            bzero(buffer, BUFFER_SIZE);

            if ((recv(client_fd, buffer, BUFFER_SIZE, 0) <= 0) and (errno != EWOULDBLOCK)) {
                disconnect_client(client_fd);
                return ;
            } else
                message.append(buffer);
        }

        // Apaga a última quebra de linha
        if (!message.empty() && message[message.size() - 1] == '\n')
            message.erase(message.size() - 1);

        // Imprime a mensagem do terminal, identificada pelo FD do usuário
        std::cout << client_fd << ": " << message << std::endl;

        // Apenas para testar. Se o usuário escreve exit(), é removido
        if (message == "exit()")
            disconnect_client(client_fd);

    } catch (const std::exception& e) {
        std::cout << "Error processing the message: " << e.what() << std::endl;
    }
}







// MÉTODOS AINDA NÃO UTILIZADOS
void Multiplexer::handle_read_event(int fd) {
    if (fd != _server_fd)
        read_client_message(fd);
    else
        connect_client(fd);
}

void Multiplexer::handle_error_event(int fd) {
    if (fd != _server_fd)
        disconnect_client(fd);
}

void Multiplexer::handle_hangup_event(int fd) {

    if (fd != _server_fd)
        disconnect_client(fd);
}

void Multiplexer::handle_write_event(int fd) {
    // send_message_to_client(fd);
    (void)fd;
    return ;
}
