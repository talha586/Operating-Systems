#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int *ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    *ptr = 10;
    if (fork() == 0)
    {
        *ptr = 99;
  	printf("Child Value: %d", *ptr); 
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("\nParent Value: %d\n", *ptr);
        munmap(ptr, sizeof(int));
    }
}
