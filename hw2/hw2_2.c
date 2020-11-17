#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

typedef struct information
{
	int i;
	char c;
}info;

void *MyThread1(void *arg)
{
	info* info1;
	info1 = (info*)arg;
	printf("%d %c\n", info1->i, info1->c);
	return (void*)0;
}

void *MyThread2(void *arg)
{
	info* info2;
	info2 = (info*)arg;
	printf("%d %c\n", info2->i, info2->c);
	return (void*)0;
}

void main()
{
	int ret1, ret2;
	pthread_t id1, id2;
	info info1;
	info1.i = 1;
	info1.c = 'o';
	info info2;
	info2.i = 2;
	info2.c = 's';
	ret1 = pthread_create(&id1, NULL, MyThread1, (void*)&info1);
	ret2 = pthread_create(&id2, NULL, MyThread2, (void*)&info2);
	if(ret1 != 0 || ret2 != 0)
	{
		printf("Create Error!\n");
	}
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
}
