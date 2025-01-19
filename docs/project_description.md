# Descrição do Projeto

## Regras gerais

- O programa não deve travar em nenhuma circunstância (mesmo quando ficar sem memória) e não deve encerrar inesperadamente.
- Deve haver um Makefile que compile os arquivos fonte:
    - Não deve fazer relink.
    - Regras mínimas: $(NAME), all, clean, fclean e re.
- O código deve ser compilado com com `c++` flags `-std=c++98`, `-Wall`, `-Wextra` e `-Werror`.
- Tente sempre desenvolver utilizando os recursos mais modernos do C++ que você puder.
    - Por exemplo, prefira usar \<cstring> ao invés de \<string.h>. Você está autorizado a usar funções da biblioteca C, mas deve preferir as versões em C++ quando possível.
- Não são permitidas bibliotecas externas nem a biblioteca **Boost**.

## Executável

Para executar o programa, utilize o comando abaixo:

```sh
./ircserv "<port>" "<password>"
```
- **<port>**: O número da porta onde o IRC Server vai ficar ouvindo as possíveis conexões.
- **<password>**: A senha de conexão. Vai ser necessário para o client tentar se conectar ao servidor.

### Pré-requisitos

- C++98 instalado na máquina

## Parte Mandatória

| Nome do Pograma | **ircserv** |
|:---|:---|
| Funções permitidas | Todas em C++ 98 e [outras funções](./allowed_functions.md) |


### Não faz parte do escopo

- Desenvolver um client
- Comunicação server-to-server

### Requerimentos

- O server deve ser capaz de lidar com múltiplos clientes ao mesmo tempo e não travar.
- A utilização de "fork" (criação de processos filhos) não é permitida.
- Todas as operações de entrada e saída (I/O) devem ser não-bloqueantes.
- Somente 1 chamada para poll() (ou equivalente) pode ser utilizada para lidar com todas essas operações (leitura, escrita, escuta, etc.).

    - É possível usar as funções read/recv ou write/send sem utilizar poll() (ou equivalente), e seu servidor não ficaria bloqueando, mas isso consumiria mais recursos do sistema. Portanto é mandatório o uso do poll() para gerenciar múltiplos fds de arquivos (não usar usar read/recv ou write/send diretamente nos fds).
    

- Escolher um [client](./clients.md) para ser utilizado no processo de avaliação.
    - Seu client de referência deve ser capaz de se conectar ao seu servidor sem encontrar nenhum erro.
- A comunicação entre o cliente e o servidor deve ser feita via TCP/IP (v4 ou v6).
- Usar o seu client com o seu servidor deve ser semelhante ao usá-lo com qualquer servidor IRC oficial. No entanto, você só precisa implementar as seguintes funcionalidades:

    - **Autenticação**: Você deve ser capaz de autenticar, definir um apelido (nickname), um nome de usuário, entrar em um canal, enviar e receber mensagens privadas usando o seu cliente de referência.
    - **Encaminhamento de mensagens**: Todas as mensagens enviadas de um cliente para um canal devem ser encaminhadas para todos os outros clientes que estiverem no canal.
    - **Usuários e operadores**: Você deve ter operadores e usuários regulares.
    - **Comandos**: Você deve implementar os comandos específicos para operadores de canal:

        | Comando | Descrição |
        |:---:|:--- |
        | KICK | Expulsar um cliente do canal. |
        | INVITE | Convidar um cliente para um canal. |
        | TOPIC | Alterar ou visualizar o tópico do canal. |
        | MODE | Alterar o modo do canal. |

        | Modos | Descrição |
        |:---:|:--- |
        | i | Definir/remover o canal somente para convidados (Invite-only). |
        | t | Definir/remover as restrições do comando TOPIC para operadores de canal. |
        | k | Definir/remover a chave (senha) do canal. |
        | o | Dar/tirar privilégios de operador de canal. |
        | l | Definir/remover o limite de usuários do canal. |

## Bônus

Features adicionais que podem ser adicionadas ao servidor de forma que se aproxime mais de um IRC real. Exemplos:

- Transferência de arquivos

    Lidar com transferência de arquivos, download e upload.

- Um bot

    Criar um bot que execute alguma operação automaticamente. Exemplo:
    - Reaction Bot: Responde a mensagens específicas.
    - Welcome bot: que envia uma mensagem personalizada quando alguém entra na sala.
    - Helper (`!help` ou `!info`) que exibe regras ou informações do canal.
    - Channel Stats Bot (`!stats`): Bot: "Estatísticas do Canal: 100 mensagens enviadas hoje. Usuário mais ativo: nick. 5 novos usuários entraram."
    - Random Bot (`!sort`): "O vencedor é: <nick>!"

- Comando para listar todos os canais:

    Adicionar um comando como /LIST para listar todos os canais ativos no servidor, permitindo que os usuários visualizem quais canais estão disponíveis para entrada.

- Histórico de mensagens:

    Manter um histórico de mensagens no servidor para que usuários que entrarem em um canal possam visualizar as mensagens passadas, mesmo se não estiverem online no momento em que as mensagens foram enviadas.

- Sistema de "whisper" (mensagens privadas):

    Permitir que os usuários enviem mensagens privadas diretamente para outros usuários, sem que outros no canal vejam.

- Reações a mensagens:

    Implementar uma funcionalidade que permita aos usuários reagirem a mensagens enviadas no canal com emojis ou símbolos (como 👍 ou 👎).

- Sistema de notificações:

    Notificar os usuários de eventos importantes, como quando alguém os convida para um canal ou quando há uma mensagem direcionada a eles especificamente.

- Sistema de "mute" de canal:

    Permitir que um canal tenha um "mute mode", onde apenas os operadores possam enviar mensagens, útil em casos de anúncios importantes.

