#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

void *MyThread1(void *args)
{
	printf("This is the thread1 running\n");
	return (void*)0;
}

void *MyThread2(void *args)
{
	printf("This is the thread2 running\n");
	return (void*)0;
}

void main()
{
	int ret1;
	int ret2;
	pthread_t id1;
	pthread_t id2;
	ret1 = pthread_create(&id1, NULL, (void*)MyThread1, NULL);
	ret2 = pthread_create(&id2, NULL, (void*)MyThread2, NULL);
	if(ret1 != 0 || ret2 != 0)
	{
		printf("Create Error!\n");
	}
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
}
