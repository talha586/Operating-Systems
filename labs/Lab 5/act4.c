#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define NUM_THREADS 5

void* print_thread(void* id)
{
	int m_id=*((int*)id);
	printf("Thread Index: %d ",m_id);
	printf(" Thread ID: %ld \n",pthread_self());
	pthread_exit(NULL);
}

int main()
{
	pthread_t workers[NUM_THREADS];
	for(int i=0;i<NUM_THREADS;i++)
	{
		int* id=malloc(sizeof(int));
		*id=i;
		pthread_create(&workers[i],NULL,print_thread,id);
	}

	for(int i=0;i<NUM_THREADS;i++)
	{
		pthread_join(workers[i],NULL);
	}
return 0;
}
