#include <stdio.h>
#include <stdlib.h>
int  main() {
	int pid, pid_filho, status;
 	printf ("\nAntes do fork pid=%d\n", getpid());
 	pid = fork();
 	if (pid == 0) {
 	printf ("pai=%d e filho=%d\n", getppid(), getpid());
 	execv ("./a.out", NULL);
 	}

	else if (pid != -1){
		pid_filho = wait(&status);
 		printf ("Depois do wait feito pelo pid=%d obtendo pid_filho=%d\n", getpid(), pid_filho);
 		exit (0);
	 }

	 else {
 		printf ("Erro no fork\n");
 		exit (-1);
 		}
 }
