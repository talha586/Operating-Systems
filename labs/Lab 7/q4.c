#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem;

void* threadA(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Data Produced\n");
        sem_post(&sem);
        sleep(1);
    }
    return NULL;
}

void* threadB(void* arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&sem);
        printf("Data Consumed\n");
    }
    return NULL;
}

int main() {
    pthread_t a, b;
    sem_init(&sem, 0, 0);

    pthread_create(&a, NULL, threadA, NULL);
    pthread_create(&b, NULL, threadB, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    sem_destroy(&sem);
    return 0;
}
