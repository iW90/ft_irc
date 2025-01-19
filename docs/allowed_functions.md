# Funções permitidas

1. socket()

- Protótipo: `int socket(int domain, int type, int protocol);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    int domain: Especifica o domínio da comunicação (ex: AF_INET para IPv4).
    int type: Tipo do socket (ex: SOCK_STREAM para TCP, SOCK_DGRAM para UDP).
    int protocol: Protocolo a ser usado (ex: 0 para o protocolo padrão de domain e type).
- Saída: Retorna um descritor de arquivo (um inteiro) que representa o socket criado ou -1 em caso de erro.

---

2. close()

- Protótipo: `int close(int fd);`
- Biblioteca: <unistd.h>
- Parâmetros:
    int fd: Descritor de arquivo (incluindo o socket) que será fechado.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

3. setsockopt()

- Protótipo: `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - int level: Nível de opção (ex: SOL_SOCKET para opções de socket).
    - int optname: Nome da opção a ser configurada (ex: SO_REUSEADDR).
    - const void *optval: Valor a ser configurado para a opção.
    - socklen_t optlen: Tamanho de optval.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

4. getsockname()

- Protótipo: `int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - struct sockaddr *addr: Ponteiro para a estrutura que receberá o endereço do socket.
    - socklen_t *addrlen: Tamanho da estrutura addr (deve ser inicialmente o tamanho da estrutura).
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

5. getprotobyname()

- Protótipo: `struct protoent *getprotobyname(const char *name);`
- Biblioteca: <netdb.h>
- Parâmetros:
    - const char *name: Nome do protocolo (ex: "tcp", "udp").
- Saída: Retorna um ponteiro para uma estrutura protoent com informações sobre o protocolo ou NULL em caso de erro.

---

6. gethostbyname()

- Protótipo: `struct hostent *gethostbyname(const char *name);`
- Biblioteca: <netdb.h>
- Parâmetros:
    - const char *name: Nome de domínio ou endereço IP.
- Saída: Retorna um ponteiro para a estrutura hostent contendo informações sobre o host ou NULL em caso de erro.

---

7. getaddrinfo()

- Protótipo: `int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);`
- Biblioteca: <netdb.h>
- Parâmetros:
    - const char *node: Nome do host ou endereço IP.
    - const char *service: Nome do serviço ou porta.
    - const struct addrinfo *hints: Ponteiro para as opções de busca.
    - struct addrinfo **res: Ponteiro onde a lista de endereços será armazenada.
- Saída: Retorna 0 em caso de sucesso ou um código de erro em caso de falha.

---

8. freeaddrinfo()

- Protótipo: `void freeaddrinfo(struct addrinfo *res);`
- Biblioteca: <netdb.h>
- Parâmetros:
    - struct addrinfo *res: Ponteiro para a lista de endereços que deve ser liberada.
- Saída: Nenhuma. Libera a memória alocada por getaddrinfo.

---

9. bind()

- Protótipo: `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - const struct sockaddr *addr: Ponteiro para a estrutura que contém o endereço a ser vinculado.
    - socklen_t addrlen: Tamanho da estrutura addr.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

10. connect()

- Protótipo: `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - const struct sockaddr *addr: Ponteiro para a estrutura que contém o endereço do servidor.
    - socklen_t addrlen: Tamanho da estrutura addr.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

11. listen()

- Protótipo: `int listen(int sockfd, int backlog);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - int backlog: Número de conexões pendentes que podem ser enfileiradas.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

12. accept()

- Protótipo: `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket que está ouvindo.
    - struct sockaddr *addr: Ponteiro para a estrutura onde o endereço do cliente será armazenado.
    - socklen_t *addrlen: Tamanho da estrutura addr.
- Saída: Retorna um novo descritor de arquivo para a conexão aceita ou -1 em caso de erro.

---

13. htons()

- Protótipo: `uint16_t htons(uint16_t hostshort);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - uint16_t hostshort: Valor de 16 bits em ordem de byte "host".
- Saída: Retorna o valor convertido para a ordem de byte "network".

---

14. htonl()

- Protótipo: `uint32_t htonl(uint32_t hostlong);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - uint32_t hostlong: Valor de 32 bits em ordem de byte "host".
- Saída: Retorna o valor convertido para a ordem de byte "network".

---

15. ntohs()

- Protótipo: `uint16_t ntohs(uint16_t netshort);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - uint16_t netshort: Valor de 16 bits em ordem de byte "network".
- Saída: Retorna o valor convertido para a ordem de byte "host".

---

16. ntohl()

- Protótipo: `uint32_t ntohl(uint32_t netlong);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - uint32_t netlong: Valor de 32 bits em ordem de byte "network".
- Saída: Retorna o valor convertido para a ordem de byte "host".

---

17. inet_addr()

- Protótipo: `in_addr_t inet_addr(const char *cp);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - const char *cp: Endereço IP em formato de string (ex: "192.168.1.1").
- Saída: Retorna o endereço IP convertido em formato de 32 bits ou INADDR_NONE em caso de erro.

---

18. inet_ntoa()

- Protótipo: `char *inet_ntoa(struct in_addr in);`
- Biblioteca: <arpa/inet.h>
- Parâmetros:
    - struct in_addr in: Estrutura contendo o endereço IP (em formato binário de 32 bits).
- Saída: Retorna o endereço IP em formato de string (ex: "192.168.1.1").

---

19. send()

- Protótipo: `ssize_t send(int sockfd, const void *msg, size_t len, int flags);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - const void *msg: Ponteiro para o buffer de dados a ser enviado.
    - size_t len: Número de bytes a serem enviados.
    - int flags: Flags adicionais de envio.
- Saída: Retorna o número de bytes enviados ou -1 em caso de erro.

---

20. recv()

- Protótipo: `ssize_t recv(int sockfd, void *buf, size_t len, int flags);`
- Biblioteca: <sys/socket.h>
- Parâmetros:
    - int sockfd: Descritor de arquivo do socket.
    - void *buf: Buffer onde os dados recebidos serão armazenados.
    - size_t len: Tamanho máximo dos dados a serem recebidos.
    - int flags: Flags adicionais de recepção.
- Saída: Retorna o número de bytes lidos ou -1 em caso de erro.

---

21. signal()

- Protótipo: `sighandler_t signal(int signum, sighandler_t handler);`
- Biblioteca: <signal.h>
- Parâmetros:
    - int signum: Número do sinal a ser tratado.
    - void (*handler)(int): Função de tratamento do sinal.
- Saída: Retorna o ponteiro para a função de tratamento anterior ou SIG_ERR em caso de erro.

---

22. sigaction()

- Protótipo: `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`
- Biblioteca: <signal.h>
- Parâmetros:
    - int signum: Número do sinal a ser tratado.
    - const struct sigaction *act: Estrutura com a nova ação a ser tomada.
    - struct sigaction *oldact: Estrutura para armazenar a ação anterior.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

23. lseek()

- Protótipo: `off_t lseek(int fd, off_t offset, int whence);`
- Biblioteca: <unistd.h>
- Parâmetros:
    - int fd: Descritor de arquivo.
    - off_t offset: Deslocamento a ser feito.
    - int whence: Posição de referência (SEEK_SET, SEEK_CUR, SEEK_END).
- Saída: Retorna o novo deslocamento em bytes ou -1 em caso de erro.

---

24. fstat()

- Protótipo: `int fstat(int fd, struct stat *statbuf);`
- Biblioteca: <sys/stat.h>
- Parâmetros:
    - int fd: Descritor de arquivo.
    - struct stat *statbuf: Estrutura onde as informações sobre o arquivo serão armazenadas.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.

---

25. fcntl()

- Protótipo: `int fcntl(int fd, int cmd, ... /* arg */ );`
- Biblioteca: <fcntl.h>
- Parâmetros:
    - int fd: Descritor de arquivo.
    - int cmd: Comando a ser executado (ex: F_SETFL para configurar flags).
    - long arg: Argumento adicional para o comando (ex: flags a serem configuradas).
- Saída: Retorna o valor solicitado pela operação ou -1 em caso de erro.

---

26. epoll()

- Protótipos: `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`
- Biblioteca: <sys/epoll.h>
- Parâmetros:
    - int epfd: Descritor de arquivo do epoll criado.
    - int op: Operação a ser realizada (EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL).
    - int fd: Descritor de arquivo a ser monitorado.
    - struct epoll_event *event: Estrutura com as informações do evento.
- Saída: Retorna 0 em caso de sucesso ou -1 em caso de erro.
- Outras funções do epoll:
    - Cria um descritor de arquivo para o epoll: `int epoll_create(int size);`
    - Aguarda eventos no descritor de arquivo epoll: `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`

> O **epoll()** também pode ser substituído por equivalentes como **select()**, **kqueue()**, or **poll()**.
