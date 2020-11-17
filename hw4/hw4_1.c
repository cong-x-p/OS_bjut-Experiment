#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

struct message
{
	int type;
	char space[1000];
};

int open_queue(int keyval)
{
	int qid;
	qid = msgget(keyval, IPC_CREAT | 0666);
	if(qid == -1)
	{
		perror("Failed in calling msgget");
		return (-1);
	}
	return (qid);
}

void main()
{
	pid_t pid;
	pid = fork();
	int qid;
	if(pid > 0)
	{
		pid = fork();
		if(pid > 0)
		{
			wait(NULL);
		}
		else
		{
			qid = open_queue(1129);
			struct message msg;
			while(1)
			{
				char input[1000];
				scanf("%s", input);
				strcpy(msg.space, input);
				msgsnd(qid, &msg, 1000, 0);
				if(input[0] == 'e'&& input[1] == 'x' && input[2] == 'i' && input[3] == 't')
				{
					break;
				}
			}
		}
	}
	else
	{
		qid = open_queue(1129);
		struct message msg;
		while(1)
		{
			msgrcv(qid, &msg, 1000, 0, 0);
			if(msg.space[0] == 'e' && msg.space[1] == 'x' && msg.space[2] == 'i' && msg.space[3] == 't')
			{
				break;
			}
			printf("%s\n", msg.space);
		}
	}
}
