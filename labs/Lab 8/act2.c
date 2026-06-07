#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5

pthread_mutex_t forks[SIZE];

void* philosopher(void* num)
{
    int p_id = *(int*)num;

    while (1)
    {

        printf("Philosopher %d is thinking...\n", p_id);
        sleep(1);

        int first_fork = p_id;
        int second_fork = (p_id + 1) % SIZE;

        if (first_fork > second_fork) 
	{
            int temp = first_fork;
            first_fork = second_fork;
            second_fork = temp;
        }

        pthread_mutex_lock(&forks[first_fork]);
        pthread_mutex_lock(&forks[second_fork]);

        printf("Philosopher %d is eating with forks %d and %d.\n", p_id, first_fork, second_fork);
        sleep(1);

        pthread_mutex_unlock(&forks[second_fork]);
        pthread_mutex_unlock(&forks[first_fork]);

        printf("Philosopher %d finished eating and put down forks.\n", p_id);
    }
}

int main()
{
    pthread_t threads[SIZE];
    int p_numbers[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        p_numbers[i] = i;
    }

    for (int i = 0; i < SIZE; i++)
    {
        pthread_create(&threads[i], NULL, philosopher, &p_numbers[i]);
    }

    for (int i = 0; i < SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }

}
