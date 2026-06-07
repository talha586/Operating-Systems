#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t sem_in[5];
sem_t sem_out[5];

void* worker(void* arg) {
    int n = *(int*)arg;
    int idx = n - 1;

    while (1) {
        sem_wait(&sem_in[idx]);
        printf("I am in %d\n", n);
        if (n < 5) sem_post(&sem_in[idx + 1]);
        else sem_post(&sem_out[0]);

        sem_wait(&sem_out[idx]);
        printf("I am out %d\n", n);
        if (n < 5) sem_post(&sem_out[idx + 1]);
        else sem_post(&sem_in[0]);
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5];

    sem_init(&sem_in[0], 0, 1);
    for (int i = 1; i < 5; i++) sem_init(&sem_in[i], 0, 0);
    for (int i = 0; i < 5; i++) sem_init(&sem_out[i], 0, 0);

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
