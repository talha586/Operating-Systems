#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{

sem_t *sem_ab = sem_open("/sem_ab", O_CREAT, 0666, 0);
sem_t *sem_bc = sem_open("/sem_bc", O_CREAT, 0666, 0);

printf("[Process A] ID: %d. Performing task...\n", getpid());
sleep(2); 

printf("[Process A] Task finished. Signaling B.\n");
sem_post(sem_ab); 

sem_close(sem_ab);
sem_close(sem_bc);
return 0;
}