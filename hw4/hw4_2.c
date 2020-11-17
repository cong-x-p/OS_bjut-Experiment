#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<math.h>
#include<string.h>

void main()
{
	int pid1, pid2;
	pid1 = fork();
	int shmid;
	int* addr;
	int* data;
	int key = 1129;
	if(pid1 > 0)
	{
		pid2 = fork();
		if(pid2 > 0)
		{
			wait(pid1);
			wait(pid2);
		}
		else
		{
			shmid = shmget(key, 1000, IPC_CREAT | 0666);
			addr = shmat(shmid, 0, 0);
			data = addr + sizeof(int);
			*addr = 0;
			for(int i = 0; i < 10; i++)
			{
				printf("input: ");
				scanf("%d", data);
				*addr = 1;
				while(*addr != 0)
				{
					sleep(0.1);
				}
			}
		}
	}
	else
	{
		shmid = shmget(key, 1000, IPC_CREAT | 0666);
		addr = shmat(shmid, 0, 0);
		data = addr + sizeof(int);
		for(int i = 0; i < 10; i++)
		{
			while(*addr != 1)
			{
				sleep(0.1);
			}
			printf("result: %d\n", (*data) * (*data));
			*addr = 0;
		}
		shmdt(addr);
		shmctl(shmid, IPC_RMID, 0);
	}
}
