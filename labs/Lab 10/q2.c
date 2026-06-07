#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define FILE_SIZE 100
#define HALF_SIZE 50

void* replace_integers(void* arg) 
{
    char* data = (char*)arg;
    for (int i = 0; i < HALF_SIZE; i++) 
    {
        if (isdigit(data[i])) 
        {
            data[i] = ' ';
        }
    }
return NULL;
}

int main(int argc, char* argv[])
{

int fd = open(argv[1], O_RDWR);
if (fd < 0) 
{ 
    perror("open"); 
    return 1; 
}

char* map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (map == MAP_FAILED) 
{ 
    perror("mmap"); 
    return 1; 
}

pthread_t thread1, thread2;

pthread_create(&thread1, NULL, replace_integers, (void*)map);

pthread_create(&thread2, NULL, replace_integers, (void*)(map + HALF_SIZE));

pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

printf("Processing complete. Integers replaced with spaces.\n");

munmap(map, FILE_SIZE);
close(fd);
return 0;
}

