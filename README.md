# ft_irc - École 42 Project

This project is an IRC server implementation in C++, inspired by **RFC 1459** and modern IRC servers. The goal is to create a lightweight, event-driven server capable of handling multiple clients, supporting IRC protocol features, and managing real-time communication across channels.

## Features

- Compliant with the **IRC protocol (RFC 1459)**.
- Handles multiple clients concurrently using **multiplexing** (epoll).
- Supports basic IRC commands such as `NICK`, `JOIN`, `PART`, `PRIVMSG`, and `QUIT`.
- Channel creation and management.
- Client nickname and user state management.
- Event-driven architecture for scalability.

## Project Structure

- **src/**: Source files for the server, client, channel management, and utilities.
- **inc/**: Header files and interfaces.
- **cfg/**: Configuration files for testing different setups.
- **log/**: Logs for server activity and debugging.

---

# ft_irc Project Roadmap

## 1. Server Setup
- **Class**: `Server`
- [x] Create a listening socket.
- [x] Bind the socket to a port.
- [x] Set the socket to listen for connections.
- [ ] Accept incoming client connections.
- [ ] Handle graceful shutdown.

---

## 2. Event Multiplexing
- **Class**: `Multiplexer`
- [x] Integrate `epoll` for efficient event-driven I/O.
- [ ] Monitor multiple sockets for incoming data or disconnections.
- [ ] Notify the server of triggered events for processing.

---

## 3. Connection Management
- **Class**: `ConnectionManager`
- [ ] Handle accepting new client connections.
- [ ] Manage client socket lifecycle (add, remove, close).
- [ ] Track active connections.

---

## 4. Client State Management
- **Class**: `Client`
- [ ] Track client nickname, username, and connection status.
- [ ] Handle message sending and receiving.
- [ ] Manage client-specific state (e.g., joined channels).
- [ ] Disconnect and clean up client resources.

---

## 5. Channel Management
- **Class**: `Channel`
- [ ] Support channel creation and destruction.
- [ ] Track clients in a channel.
- [ ] Manage channel topics, modes, and permissions.
- [ ] Broadcast messages to all channel members.

---

## 6. Message Parsing and Processing
- **Class**: `MessageProcessor`
- [ ] Parse raw messages from clients.
- [ ] Process IRC commands (e.g., `NICK`, `JOIN`, `PART`, `PRIVMSG`).
- [ ] Route messages to the appropriate client(s) or channel(s).
- [ ] Handle server-specific commands (e.g., `PING/PONG`).

---

## 7. Protocol Compliance
- **Class**: `IRCProtocolHandler`
- [ ] Implement core IRC protocol features (e.g., registration, error responses).
- [ ] Ensure compliance with RFC 1459.
- [ ] Handle edge cases and malformed commands.

---

## 8. Configuration Handling
- **Class**: `ConfigParser`
- [ ] Parse a configuration file for server settings (e.g., port, max clients).
- [ ] Use configuration to initialize the server.

---

## 9. Logging and Debugging
- **Class**: `Logger`
- [ ] Log server events (connections, disconnections, errors).
- [ ] Log client commands and interactions for debugging.
- [ ] Provide configurable logging levels (e.g., INFO, DEBUG, ERROR).

---

## 10. Error Handling
- **Class**: `ErrorHandler`
- [ ] Handle invalid commands and protocol violations.
- [ ] Send appropriate error messages to clients (e.g., `ERR_UNKNOWNCOMMAND`).
- [ ] Gracefully handle client disconnections and socket errors.


--- 

## Additional Notes
- Focus on a robust, modular design with clear separation of concerns.
- Use `epoll` for scalability, enabling efficient handling of hundreds of simultaneous connections.
- Start with basic IRC features and progressively implement advanced functionality.


```
/ft_irc
│
├── /src
│   ├── /application
│   │   ├── /usecases
│   │   │   ├── ClientAuthentication.hpp
│   │   │   ├── JoinChannel.hpp
│   │   │   ├── SendMessage.hpp
│   │   │   └── SetTopic.hpp
│   │   └── /services
│   │       ├── ChannelService.hpp
│   │       ├── UserService.hpp
│   │       └── ConnectionService.hpp
│   │
│   ├── /domain
│   │   ├── /entities
│   │   │   ├── Client.hpp
│   │   │   ├── Channel.hpp
│   │   │   └── Message.hpp
│   │   ├── /interfaces
│   │   │   ├── IChannelRepository.hpp
│   │   │   ├── IUserRepository.hpp
│   │   │   └── IConnectionManager.hpp
│   │   └── /exceptions
│   │       └── Exceptions.hpp
│   │
│   ├── /infrastructure
│   │   ├── /repositories
│   │   │   ├── ChannelRepository.hpp
│   │   │   └── UserRepository.hpp
│   │   └── /network
│   │       ├── ServerSocket.hpp
│   │       ├── ClientHandler.hpp
│   │       └── PollManager.hpp
│   │
│   ├── /interface
│   │   ├── /controllers
│   │   │   ├── ClientController.hpp
│   │   └── /views
│   │       ├── CommandParser.hpp
│   │       └── MessageFormatter.hpp
│   │
│   └── main.cpp
│
├── Makefile
└── README.md

```


```

/ircserv
│
├── Makefile               # Arquivo Makefile para compilação
├── src/                   # Código-fonte principal
│   ├── Application/       # Camada de aplicação
│   │   ├── IRCServer.hpp  # Classe principal do servidor IRC
│   │   ├── IRCServer.cpp  # Implementação da classe do servidor IRC
│   │   └── CommandHandler.hpp  # Interface para lidar com comandos
│   │
│   ├── Domain/            # Camada de domínio (modelos de dados)
│   │   ├── Client.hpp     # Classe representando um cliente conectado
│   │   ├── Client.cpp     # Implementação da classe Client
│   │   ├── Channel.hpp   # Classe representando um canal
│   │   ├── Channel.cpp   # Implementação da classe Channel
│   │   └── Message.hpp   # Classe para mensagens IRC
│   │
│   ├── Infrastructure/    # Camada de infraestrutura
│   │   ├── Socket.hpp     # Classe para manipulação de sockets
│   │   ├── Socket.cpp     # Implementação da classe Socket
│   │   ├── Poller.hpp     # Classe para configuração do poll()
│   │   ├── Poller.cpp     # Implementação da classe Poller
│   │   └── Utils.hpp      # Funções auxiliares, como conversões de dados
│   │
│   ├── Interface/         # Camada de interface com o usuário/cliente
│   │   ├── CommandParser.hpp  # Responsável por parsear os comandos
│   │   └── CommandParser.cpp  # Implementação da classe CommandParser
│   │
│   └── main.cpp           # Ponto de entrada do servidor
│
├── include/               # Arquivos de cabeçalho (.hpp)
│   └── (contém todos os .hpp de cada classe)
│
└── tests/                 # Testes unitários
    ├── DomainTests/       # Testes para as classes de domínio
    │   └── ClientTests.cpp
    ├── ApplicationTests/  # Testes para a camada de aplicação
    │   └── IRCServerTests.cpp
    └── InfrastructureTests/ # Testes para a camada de infraestrutura
        └── SocketTests.cpp
```