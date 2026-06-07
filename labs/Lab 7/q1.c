#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 1000;
pthread_mutex_t lock;

void* withdraw(void* arg) {
    pthread_mutex_lock(&lock);
    int amount = 100;
    if (balance >= amount) {
        int temp = balance;
        sleep(1); 
        balance = temp - amount;
        printf("Withdrawn: %d, New Balance: %d\n", amount, balance);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, withdraw, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Balance: %d\n", balance);
    pthread_mutex_destroy(&lock);
    return 0;
}
