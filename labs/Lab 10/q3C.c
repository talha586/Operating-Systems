#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
sem_t *sem_ab = sem_open("/sem_ab", 0);
sem_t *sem_bc = sem_open("/sem_bc", 0);

printf("[Process C] Waiting for B...\n");
sem_wait(sem_bc);

printf("[Process C] ID: %d. Final task executed.\n", getpid());

sem_close(sem_ab);
sem_close(sem_bc);
sem_unlink("/sem_ab");
sem_unlink("/sem_bc");
return 0;
}