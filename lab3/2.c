#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int contador_ctrl_c = 0; // Contador de SIGINT (CTRL-C)

// Manipulador de sinal para SIGINT (CTRL-C)
void handle_sigint(int sig)
{
    contador_ctrl_c++;
    printf("\nCTRL-C pressionado %d vezes\n", contador_ctrl_c);

    if (contador_ctrl_c >= 5)
    {
        printf("Deseja realmente sair? (s/n): ");
        char resposta;
        scanf(" %c", &resposta);
        if (resposta == 's' || resposta == 'S')
        {
            printf("Saindo do programa...\n");
            exit(0);
        }
        else
        {
            contador_ctrl_c = 0; // Reseta o contador
        }
    }
}

// Manipulador de sinal para SIGTSTP (CTRL-Z)
void handle_sigtstp(int sig)
{
    printf("\nNúmero de CTRL-C pressionados até agora: %d\n", contador_ctrl_c);
}

int main()
{
    // Configura os manipuladores de sinal
    signal(SIGINT, handle_sigint);   // Captura CTRL-C
    signal(SIGTSTP, handle_sigtstp); // Captura CTRL-Z

    // Loop infinito para manter o programa rodando
    while (1)
    {
        printf("Programa rodando... Pressione CTRL-C ou CTRL-Z\n");
        sleep(1); // Evita uso excessivo de CPU
    }

    return 0;
}
