#include <stdio.h>
#include <unistd.h>

 int main()
 {
 	if (fork() && (fork())) {
 		if (fork() || fork()) {
 			fork();
 					}
 				}
printf("Hello world!, process_id(pid) = %d \n",getpid());
	printf("1\n");
 	return 0;
 }
