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
│   │       ├── ServerService
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
│   │       └── ServerException
│   │
│   └── /infrastructure
│       └── /network
│           ├── Socket
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