#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

void main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		pid = fork();
		if(pid > 0)
		{
			printf("a, %d\n", getpid());
		}
		else if(pid == 0)
		{
			printf("b, %d\n", getpid());
		}
	}
	else if(pid == 0)
	{
		printf("c, %d\n", getpid());
	}
}
