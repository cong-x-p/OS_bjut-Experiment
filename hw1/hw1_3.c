#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void main()
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		pid = fork();
		if(pid == 0)
		{
			wait(NULL);
			char content[100];
			read(fd[0], content, 31 * sizeof(char));
			printf("%s\n", content);
			read(fd[0], content, 31 * sizeof(char));
			printf("%s\n", content);
		}
		else
		{
			write(fd[1], "Child 1 is sending a message!\n", 31 * sizeof(char));
		}
	}
	else
	{
		write(fd[1], "Child 2 is sending a message!\n", 31 * sizeof(char));
	}

}
