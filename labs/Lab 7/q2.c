#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void* print_thread(void* arg) {
    long tid = (long)arg;
    pthread_mutex_lock(&lock);
    for (int i = 1; i <= 3; i++) {
        printf("Thread %ld printing: %d\n", tid, i);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[3];
    pthread_mutex_init(&lock, NULL);

    for (long i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_thread, (void*)(i + 1));
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
