#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void temp(char c)
{
	for(int i = 0; i < 1000; i++)
	{
		printf("%c", c);
	}
	printf("\n");
}

void main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		pid = fork();
		if(pid > 0)
		{
			temp('a');
		}
		else if(pid == 0)
		{
			temp('b');
		}
	}
	else if(pid == 0)
	{
		temp('c');
	}
}
