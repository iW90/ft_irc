# Clean Arch

## Estrutura de diretórios

```
/irc_server
│
├── /src
│   ├── /application
│   │   ├── /usecases
│   │   │   ├── ClientAuthentication
│   │   │   ├── JoinChannel
│   │   │   ├── SendMessage
│   │   │   └── SetTopic
│   │   └── /services
│   │       ├── ChannelService
│   │       ├── UserService
│   │       ├── CommandService
│   │       └── ConnectionService
│   │
│   ├── /domain
│   │   ├── /entities
│   │   │   ├── Server
│   │   │   ├── Client
│   │   │   ├── Channel
│   │   │   └── Message
│   │   ├── /enums
│   │   │   └── Xxxx
│   │   └── /exceptions
│   │       └── Xxxx
│   │
│   └── /infrastructure
│       └── /network
│           ├── ServerSocket
│           ├── Multiplexer (ClientHandler)
│           └── PollManager
│
├── /includes
│   └── (contém todos os .hpp de cada classe)
│
└── main.cpp
```

## Detalhamento

/soon