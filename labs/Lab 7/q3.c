#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t computers;

void* student(void* arg) {
    long id = (long)arg;
    
    sem_wait(&computers);
    printf("Student %ld is sitting down at a computer\n", id);
    sleep(2);
    printf("Student %ld is leaving the computer\n", id);
    sem_post(&computers);
    
    return NULL;
}

int main() {
    pthread_t students[7];
    sem_init(&computers, 0, 3);

    for (long i = 0; i < 7; i++) {
        pthread_create(&students[i], NULL, student, (void*)(i + 1));
    }

    for (int i = 0; i < 7; i++) {
        pthread_join(students[i], NULL);
    }

    sem_destroy(&computers);
    return 0;
}
