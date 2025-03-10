#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("Uso: %s <executavel> [parametro]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { // Processo filho
        char *args[4]; // Array de argumentos para execvp (máximo de 3 argumentos + NULL)
        args[0] = argv[1];  // Nome do arquivo executável
        args[1] = (argc == 3) ? argv[2] : NULL; // Parâmetro opcional
        args[2] = NULL; // Terminador necessário para execvp
        printf("[CHILD]: About to load command.\n");
        execvp(args[0], args);
        perror("execvp"); // Se execvp falhar
        exit(EXIT_FAILURE);
    }
    else
    {               // Processo pai
        printf("[PARENT]: Waiting on child.\n");
        wait(NULL); // Espera o processo filho terminar
        printf("[PARENT]: Child finished.\n");
    }

    return 0;
}
