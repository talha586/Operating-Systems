#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
sem_t *sem_ab = sem_open("/sem_ab", 0); 
sem_t *sem_bc = sem_open("/sem_bc", 0);

printf("[Process B] Waiting for A...\n");
sem_wait(sem_ab); 

printf("[Process B] ID: %d. Performing task...\n", getpid());
sleep(1);

printf("[Process B] Task finished. Signaling C.\n");
sem_post(sem_bc); 

sem_close(sem_ab);
sem_close(sem_bc);
return 0;
}