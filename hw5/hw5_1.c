#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("%d received SIGUSR1\n", getpid());
	}
	else if(signo == SIGINT)
	{
		printf("%d received SIGINT\n", getpid());
	}
}

int main()
{
	pid_t pid;
	pid = fork();
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		printf("can't catch SIGUSR1\n");
		return 0;
	}
	if(signal(SIGINT, sig_usr) == SIG_ERR)
	{
		printf("can't catch SIGINT\n");
		return 0;
	}
	for( ; ; ) pause();
	return 0;
}
