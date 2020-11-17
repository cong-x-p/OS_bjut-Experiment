#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include"semaphore.h"

int buffer[2];
int N = 2;
sem_t s, n, e;
int in = 0;
int out = 0;
int end1 = 0, end2 = 0;

int put(int data)
{
	buffer[in] = data;
	in = (++in) % N;
	return 0;
}

int take()
{
	int res = buffer[out];
	out = (++out) % N;
	return res;
}

void *MyOperate1(void* arg)
{
	while(1)
	{
		sem_wait(&n);
		sem_wait(&s);
		int data1 = take();
		sem_post(&s);
		sem_post(&e);

		sem_wait(&n);
		sem_wait(&s);
		int data2 = take();
		sem_post(&s);
		sem_post(&e);

		printf("%d + %d = %d\n", data1, data2, data1 + data2);
		if(end1 == 1 && end2 == 1) break;
	}
	return (void*) 0;
}

void *MyOperate2(void* arg)
{
	while(1)
	{
		sem_wait(&n);
		sem_wait(&s);
		int data1 = take();
		sem_post(&s);
		sem_post(&e);

		sem_wait(&n);
		sem_wait(&s);
		int data2 = take();
		sem_post(&s);
		sem_post(&e);

		printf("%d * %d = %d\n", data1, data2, data1 * data2);
		if(end1 == 1 && end2 == 1) break;
	}
	return (void*) 0;
}

void *MyRead1(void* arg)
{
	FILE* stream;
	stream = fopen("/home/cxp/hw3/1.dat", "r");
	while(1)
	{
		int data1;
	       	if(fscanf(stream, "%d", &data1) == EOF)
		{
			break;
		}
		sem_wait(&e);
		sem_wait(&s);
		put(data1);
		sem_post(&s);
		sem_post(&n);
	}
	end1 = 1;
}

void *MyRead2(void* arg)
{
	FILE* stream;
	stream = fopen("/home/cxp/hw3/2.dat", "r");
	while(1)
	{
		int data2;
		if(fscanf(stream, "%d", &data2) == EOF)
		{
			break;
		}
		sem_wait(&e);
		sem_wait(&s);
		put(data2);
		sem_post(&s);
		sem_post(&n);
	}
	end2 = 1;
}

void main()
{
	int ret1, ret2, ret3, ret4;
	pthread_t op1, op2;
	pthread_t read1, read2;
	sem_init(&n, 0, 0);
	sem_init(&s, 0, 1);
	sem_init(&e, 0, 2);
	ret1 = pthread_create(&op1, NULL, MyOperate1, NULL);
	ret2 = pthread_create(&op2, NULL, MyOperate2, NULL);
	ret3 = pthread_create(&read1, NULL, MyRead1, NULL);
	ret4 = pthread_create(&read2, NULL, MyRead2, NULL);
	if(ret1 != 0 || ret2 != 0 || ret3 != 0 || ret4 != 0)
	{
		printf("Create Error!\n");
	}
	pthread_join(op1, NULL);
	pthread_join(op2, NULL);
	pthread_join(read1, NULL);
	pthread_join(read2, NULL);
}
