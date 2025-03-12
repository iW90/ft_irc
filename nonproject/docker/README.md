
## Usando docker para instancias de client (weechat)

### No diretório /docker (onde está o Dockerfile) utilize o comando
```docker build -t irc-client .```


### Depois de construído, você poderá se conectar no weechat usando
```./connect.sh <username>```


### Já dentro do programa, utilizará o 
```/connect bestserver```