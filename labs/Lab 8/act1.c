#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5 

int arr[SIZE];
int fill = 0;
int clear = 0;

sem_t sem1;
sem_t sem2;
pthread_mutex_t mutex;

void* producer_worker(void* param)
{
    int worker_id = *((int*)param);

    for(int i = 0; i < 5; i++) 
    {
        int value = rand() % 100; 

        sem_wait(&sem1);
        pthread_mutex_lock(&mutex);

        arr[fill] = value;
        printf("Producer %d put item %d in slot %d\n", worker_id, value, fill);
        fill = (fill + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem2);
        sleep(1);
    }

    return NULL;
}

void* consumer_worker(void* param) 
{
    int worker_id = *((int*)param);

    for(int i = 0; i < 5; i++) 
    {
        sem_wait(&sem2);
        pthread_mutex_lock(&mutex);

        int value = arr[clear];
        printf("Consumer %d took item %d from slot %d\n", worker_id, value, clear);
        clear = (clear + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem1);
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t prods[2], cons[2];
    int ids[2] = {1, 2};

    sem_init(&sem1, 0, SIZE);
    sem_init(&sem2, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < 2; i++)
    {
        pthread_create(&prods[i], NULL, producer_worker, &ids[i]);
        pthread_create(&cons[i], NULL, consumer_worker, &ids[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        pthread_join(prods[i], NULL);
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    pthread_mutex_destroy(&mutex);

}

