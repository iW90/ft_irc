# SOCKET

Um socket permite que os programas troquem dados entre si, seja na mesma máquina ou através de uma rede (como a internet). Ele atua como um ponto final para a comunicação de rede.

É identificado por três componentes:

- **Endereço IP**: O endereço do dispositivo (computador) na rede, como um endereço IPv4 (ex.: 192.168.0.1).

- **Porta**: Um número que identifica um serviço ou processo específico no computador. Cada serviço em um computador que usa rede precisa de uma porta única para comunicação. Exemplos de portas são:

    - Porta 80 para servidores web (HTTP).
    - Porta 443 para HTTPS (HTTP seguro).
    - Porta 6667 para IRC (Internet Relay Chat).

- **Protocolo**: O tipo de protocolo de comunicação que o socket vai usar. Usaremos o TCP:

    - **TCP (Transmission Control Protocol)**: Protocolo orientado à conexão, que garante a entrega dos dados de forma confiável.

## Como funciona

Existem dois tipos principais de sockets, baseados em como a comunicação é feita, o de Servidor e o de Client (lembrando que não criaremos um Client):

1. Sockets de Servidor (servidores escutando):

    O servidor cria um socket para "escutar" solicitações de conexão dos clientes.
    O servidor então se "liga" a um endereço IP e a uma porta específica, e começa a esperar por conexões.
    Quando um cliente se conecta, o servidor aceita a conexão e começa a se comunicar com o cliente.

2. Sockets de Cliente (clientes conectando):

    O cliente cria um socket para se conectar ao servidor, especificando o endereço IP e a porta do servidor.
    Depois de estabelecida a conexão, o cliente pode enviar ou receber dados do servidor.


## Como usar

Aqui está um esboço do que acontece durante a comunicação:

- Servidor:
    - Cria um socket.
    - Associa esse socket a um endereço IP e a uma porta usando a função `bind()`.
    - Começa a "escutar" por conexões com `listen()`.
    - Aceita conexões com `accept()`.

- Cliente:
    - Cria um socket.
    - Conecta-se ao servidor com `connect()` usando o endereço IP e a porta do servidor.

- Troca de Dados:
    - Uma vez estabelecida a conexão, tanto o servidor quanto o cliente podem enviar e receber dados usando as funções send() e recv() (ou write() e read(), dependendo da plataforma), mas usaremos a função `epoll()` para gerenciar estes processos.

- Fechamento da Conexão:
    - Quando a comunicação termina, ambos os lados fecham a conexão com `close()`.

