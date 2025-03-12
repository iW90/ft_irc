
## Usando docker para instancias de client (weechat)

### No diretório /docker (onde está o Dockerfile) utilize o comando
```docker build -t irc-client .```


### Depois de construído, você poderá se conectar no weechat usando
```./connect.sh```


### Já dentro do programa, utilizará o 
```/connect bestserver```


### Comandos uteis de docker
para listar as imagens de containers que você criou (e as hashes)
```docker image ls```

