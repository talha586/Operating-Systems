#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() 
{
    int *counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *counter = 0;

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        for (int i = 0; i < 5; i++) {
            (*counter)++;
            printf("Child 1 Counter: %d\n", *counter);
            usleep(1000);
        }
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        for (int i = 0; i < 5; i++) {
            (*counter)++;
            printf("Child 2 Counter: %d\n", *counter);
            usleep(1000);
        }
        exit(0);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Final Counter Value: %d\n", *counter);

    munmap(counter, sizeof(int));

}
