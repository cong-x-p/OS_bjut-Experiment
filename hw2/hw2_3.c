#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

void *MyThread1(void* arg)
{
	int* array1;
	array1 = (int*) arg;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(array1[j] > array1[j + 1])
			{
				int tmp = array1[j];
				array1[j] = array1[j + 1];
				array1[j + 1] = tmp;
			}
		}
	}
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", array1[i]);
	}
	printf("\n");
	return (void*)0;
}

void *MyThread2(void* arg)
{
	int* array2;
	array2 = (int*) arg;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(array2[j] < array2[j + 1])
			{
				int tmp = array2[j];
				array2[j] = array2[j + 1];
				array2[j + 1] = tmp;
			}
		}
	}
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", array2[i]);
	}
	printf("\n");
	return (void*)0;
}
void main()
{
	int ret1, ret2;
	pthread_t id1, id2;
	int array1[10] = {3, 2, 1, 5, 4, 6, 8, 7, 10, 9};
	int array2[10] = {3, 2, 1, 5, 4, 6, 8, 7, 10, 9};
	ret1 = pthread_create(&id1, NULL, MyThread1, (void*)array1);
	ret2 = pthread_create(&id2, NULL, MyThread2, (void*)array2);
	if(ret1 != 0 || ret2 != 0)
	{
		printf("Create Error!\n");
	}
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

}
