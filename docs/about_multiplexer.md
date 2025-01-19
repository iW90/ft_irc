# MULTIPLEXADOR DE ENTRADA E SAÍDA

Em sistemas operacionais, multiplexação de I/O (Input/Output Multiplexing) se refere à habilidade de monitorar múltiplos canais de entrada/saída (como conexões de rede, arquivos, etc.) ao mesmo tempo, sem bloquear a execução do programa.

Isso é importante quando você quer que seu programa manipule várias conexões de rede simultaneamente, mas sem ficar esperando indefinidamente por cada uma delas.

No contexto de um servidor de IRC, por exemplo, você poderia ter múltiplos usuários conectados ao mesmo tempo. Usar um multiplexador de I/O permite que você **não** precise criar uma nova thread ou processo para cada usuário. Em vez disso, o multiplexador verifica várias conexões simultaneamente e te avisa quando uma delas tem dados prontos para ler ou escrever.


## Epoll

É uma API que oferece uma maneira eficiente de fazer multiplexação de I/O em sistemas Linux. É uma evolução de técnicas mais antigas, como o `select()`, e foi projetada para ser mais escalável e eficiente quando você tem muitas conexões para monitorar.

O epoll é usado para monitorar eventos de entrada/saída em descritores de arquivo, que no caso de um servidor TCP, são as conexões de rede com os clientes.


### Como o epoll funciona?

- **Criar um "epoll instance"**: você cria uma instância do epoll, que vai armazenar e monitorar os eventos que você está interessado.
- **Registrar FD's**: você registra os sockets (conexões de rede) com a instância do epoll, especificando os eventos que você deseja monitorar (leitura, escrita, etc.).
- **Esperar por eventos**: o epoll espera e retorna quando qualquer um dos eventos monitorados ocorre.
- **Processar eventos**: quando um evento é detectado, você pode agir sobre ele, como ler ou escrever dados na conexão.
- **Desregistrar e limpar**: quando terminar, você desregistra os descritores de arquivo e libera os recursos.

