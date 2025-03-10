/* PROGRAMA P1 */
#include <stdio.h>
#include <unistd.h>
int main()
{
	if (fork() || fork())
		fork();
	printf("1\n");
    	//printf("Hello world!, process_id(pid) = %d \n",getpid());

	return 0;
}
