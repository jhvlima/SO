# Comando ps

## Exercício 1: 
Reproduza os exemplos acima de uso do ps, e experimente também usá-lo com a opção "u":. Use "ps u" e
depois "ps aux". Qual a diferença que você observou na saída?

```bash
ps 
ps u
ps aux
```

### Resposta
Para o comando 'ps' default mostra os processos em execução no proprio terminal bash. Os campos mostrados são: process ID (PID), teminal associado (TTY), tempo acumulado na cpu (TIME), nome do executavel (CMD).
Para o 'ps u' mostra todos os processos do usuário no terminal autal, além de dar mais detalhes como usuário, uso de CPU e memória, e estado do processo.
Para o 'ps aux' mostra todos os processos do sistema e os mesmos detalhes do `ps u` 

## Exercício 2: 
Invoque a man page do ps com "man ps" e leia nela o que significa o campo "STAT". Lembre-se que você pode localizar palavras ao ler uma man page com o comando "/" (para uma lista de comandos pressione ‘h’; para sair do manual, pressione ‘q’).
Agora olhe novamente a saída do comando “ps aux” e responda: por que a grande maioria dos processos apresenta a letra ‘S’ na coluna STAT, e pouquíssimos (1 ou 2?!?) a letra ‘R’?

```bash
man ps
```
### Resposta
STAT siginfica estado do processo.
S significa interruptible sleep, ou seja, o processo está inativo, esperando a conclusão de um evento para ser executado. 
R significa running ou runnable, ou seja, o processo está sendo executado ou está pronto para execução numa fila de execução.
Existem apenas dois processos com status R e muitos com status S porque no momento que o comando 'ps aux' foi chamado os outros processos do sistema esperaram o processo do 'ps' terminar.

## Exercício 3: 
Em geral há um limite superior pequeno para o PID que um processo pode ter (por exemplo 32767). O que você acha que acontece quando esse limite é atingido?

### Resposta
Acredito que PID recomeçe do menor valor não utilizado.
E para verificar o que acontece fizemos um programa para testar isso

```bash
#!/bin/bash
while true; do
    ps
done
```

    PID TTY          TIME CMD
    10 pts/0        00:00:00 bash
    31696 pts/0     00:00:00 bash
    32767 pts/0     00:00:00 ps

    PID TTY          TIME CMD
    10 pts/0        00:00:00 bash
    300 pts/0       00:00:00 ps
    31696 pts/0     00:00:00 bash


# Execução em Background 

## Exercício 4: 
Crie um subdiretório, coloque nele vários arquivos e use-o para disparar a compressão em background, como indicado acima. Em seguida, execute outros comandos, por exemplo:
```bash
mkdir lixo
cd lixo
cp ~/bin/* .
gzip -9 * &
ps u
# (... outros comandos ... o comando abaixo vai apagar seu diretório lixo)
rm -rf lixo
```

### Resposta
Na penultima linha está o processo de compactação que exije bastante da cpu

    (base) chefe@DESKTOP-L0MSLR4:~/ufes/2024_02/SO/lab0/lixo$ ps u
    USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
    chefe       10  0.0  0.0   6488  5572 pts/0    Ss   10:24   0:00 -bash
    chefe       92  0.0  0.0   2892   972 pts/1    Ss+  10:29   0:00 sh -c "$VSCODE_WSL_EXT_L
    chefe       93  0.0  0.0   2892   948 pts/1    S+   10:29   0:00 sh /mnt/c/Users/p3dro/.v
    chefe       98  0.0  0.0   2892   924 pts/1    S+   10:29   0:00 sh /home/chefe/.vscode-s
    chefe      102  0.2  1.1 11801972 92504 pts/1  Sl+  10:29   0:08 /home/chefe/.vscode-serv
    chefe      115  0.0  0.7 1001696 60492 pts/2   Ssl+ 10:29   0:00 /home/chefe/.vscode-serv
    chefe      124  0.1  0.6 991296 52332 pts/3    Ssl+ 10:29   0:04 /home/chefe/.vscode-serv
    chefe      138  0.0  0.7 11726512 59508 pts/1  Sl+  10:29   0:01 /home/chefe/.vscode-serv
    chefe      168  2.2  1.9 32840928 160568 pts/1 Sl+  10:29   1:20 /home/chefe/.vscode-serv
    chefe      321  0.0  0.6 994508 54192 pts/1    Sl+  10:29   0:00 /home/chefe/.vscode-serv
    chefe      443  0.1  0.8 997544 64916 pts/1    Sl+  10:30   0:04 /home/chefe/.vscode-serv
    chefe     2326  0.0  0.0   6256  5164 pts/4    Ss+  11:21   0:00 -bash
    chefe     3569 79.5  0.0   3656  1996 pts/0    R    11:28   0:29 gzip -9 GET HEAD NF POST
    chefe     3681  0.0  0.0   7484  3172 pts/0    R+   11:29   0:00 ps u

# Prioridade

## Exercício 5: 
De dentro do seu diretório ~/lixo, execute os seguintes comandos (mas antes, esvazie seu diretório lixo e copie novamente os arquivos do /bin para dentro dele):

```bash
nice -n 15 gzip -9 * &
ps l
```
Você acabou de criar um processo em background usando o comando nice e alterando sua prioridade. Em seguida, você listou os processos (“ps l”) visualizando, entre outros atributos, suas prioridades (colunas PRI e NI). Observe que o valor de PRI para o processo gzip foi 20+15 (o mesmo 15 que você passou no parâmetro ajuste), o que resulta em um número maior do que dos outros processos. Como no Linux os valores de prioridades são invertidos (número menor, prioridade maior), com este procedimento, você reduziu a prioridade do gzip. Você também poderia ter aumentado a prioridade do processo, passando um valor negativo no parâmetro ajuste mas, para isso, você precisaria ser superusuário. Você saberia dizer por que há essa restrição? Extra: Leia a man page do comando renice para saber como alterar a prioridade de um processo após o seu disparo

### Resposta
Passar como parametro um valor negativo pode ser perigoso uma vez que se um processo demorado tenha controle da cpu, processos importantes podem ser comprometidos. Processos críticos do sistema precisam ter prioridade garantida, e permissões de superusuário evitam que usuários comuns alterem isso de forma prejudicial.

Comandos no terminal

    (base) chefe@DESKTOP-L0MSLR4:~/ufes/2024_02/SO/lab0/lixo$ nice -n 15 gzip -9 * &
    [1] 4718
    (base) chefe@DESKTOP-L0MSLR4:~/ufes/2024_02/SO/lab0/lixo$ ps l
    F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
    4  1000    10     9  20   0   7120  6120 do_wai Ss   pts/0      0:00 -bash
    4  1000    92    91  20   0   2892   972 do_wai Ss+  pts/1      0:00 sh -c "$VSCODE_WSL_EXT_LOCATION/scripts/wslServer.sh" fabdb6a30b
    0  1000    93    92  20   0   2892   948 do_wai S+   pts/1      0:00 sh /mnt/c/Users/p3dro/.vscode/extensions/ms-vscode-remote.remote
    0  1000    98    93  20   0   2892   924 do_wai S+   pts/1      0:00 sh /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b
    0  1000   102    98  20   0 11808372 96220 -    Sl+  pts/1      0:10 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    4  1000   115   114  20   0 1001696 61020 -     Ssl+ pts/2      0:01 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    4  1000   124   123  20   0 991296 52692 -      Ssl+ pts/3      0:04 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    0  1000   138   102  20   0 11727492 60984 -    Sl+  pts/1      0:02 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    0  1000   168   102  20   0 32841952 164340 -   Sl+  pts/1      1:30 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    0  1000   321   168  20   0 994508 54192 -      Sl+  pts/1      0:00 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    0  1000   443   168  20   0 997544 65080 -      Sl+  pts/1      0:04 /home/chefe/.vscode-server/bin/fabdb6a30b49f79a7aba0f2ad9df9b399
    4  1000  2326  2325  20   0   6256  5164 core_s Ss+  pts/4      0:00 -bash
    0  1000  4718    10  35  15   3660  1888 -      RN   pts/0      0:02 gzip -9 GET HEAD NF POST [ aa-enabled aa-exec aa-features-abi ab
    0  1000  4731    10  20   0   7484  3024 -      R+   pts/0      0:00 ps l
    (base) chefe@DESKTOP-L0MSLR4:~/ufes/2024_02/SO/lab0/lixo$ ps l

# Environment

## Exercício 7: 
Examine o valor da variável PAGER. Um modo de fazer isso é executar o comando "echo $PAGER". O comando "set" executado sem argumentos exibe todas as variáveis atualmente definidas. Execute esse comando também.
```bash
echo $PAGER
set
```

## Exercício 8: 
Atribua repetidamente "more" e "less" para a variável PAGER conforme os exemplos acima executando também uma leitura de man page (por exemplo "man ps") para confirmar a troca do paginador. 

### Resposta

Nesse caso, ele pula de pagina em pagina
```bash
PAGER=more
export PAGER
man ps
```

Nesse caso, ele pula de linha em linha

```bash
PAGER=less
export PAGER
man ps
```

## Exercício 9: 
Examine o(s) arquivo(s) de inicialização do shell que você usa para saber quais variáveis são criadas ou inicializadas neles. Esses arquivos são citados em geral no final da man page (seção "FILES"). No Linux, temos os arquivos “.bashrc”, que estão presentes no home, no diretório “/etc/skel/” e “/root”. Além de variáveis de ambientes, o usuário também pode definir “alias” para comandos. Um excelente alias é o “ll” para executar o comando “ls -alF”. Defina esse comando no seu “.bashrc” (basta adicionar a linha “alias ll='ls -alF'). 

### Resposta

Já está incluido os `alias` para o comando `ls`

```bash
nano ~/.bashrc
```

```bash
# some more ls aliase
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
```

```bash
source ~/.bashrc
```

## Exercício 10: 
No Unix, mesmo algumas operações extremamente simples como listar os arquivos de um diretório envolvem o disparo de pelo menos um novo processo. No entanto, a troca do diretório corrente (comando "cd") não provoca o disparo de processo algum. Você saberia explicar porquê?


### Resposta
O `cd` é um programa inbutido no Shell, isso é importante porque o modo de execusão de um programa executavel não funcionaria da maneira esperada para o `cd`. Se o `cd` fosse um programa executável pelo shell, o fluxo de execução seria:

1. fazer um fork para o filho executar o programa `cd`
2. no processo do filho fazer a troca de diretorio saindo da raiz e indo pra o diretorio desejado
3. finalizar o processo filho do `cd`
4. voltar para o processo pai sem alteração de diretórios

Dessa forma o diretorio atual não seria alterado.

Referencia de discussões sobre a questão 10:

> https://www.quora.com/Unix-Why-is-cd-a-built-in-command-in-the-shell-and-not-an-executable-program-like-the-command-ls

> https://unix.stackexchange.com/questions/38808/why-is-cd-not-a-program
