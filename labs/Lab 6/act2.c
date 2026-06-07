#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define N 10
#define M 2

int main() {
    key_t key = ftok("shmfile", 65);
    size_t total_size = (N + M + 1) * sizeof(int);

    int shmid = shmget(key, total_size, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Error shmget");
        exit(1);
    }

    int *base_ptr = (int *)shmat(shmid, NULL, 0);
    if (base_ptr == (void *)-1)
    {
        perror("Error shmat");
        exit(1);
    }

    int *numbers = base_ptr;              
    int *partial_sums = base_ptr + N;     
    int *final_sum = base_ptr + N + M;    

    srand(time(NULL));
   
    for (int i = 0; i < N; i++)
    {
        numbers[i] = rand() % 100;
    }

    for(int i = 0;i < N ; i++)
    {
	printf("%d ", numbers[i]);
    }

    int size = N / M;
 
    for (int i = 0; i < M; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            int start = i * size;
            int end;

            if (i == M - 1)
	    {
                end = N;
            }
 
	    else 
            {
                end = (i + 1) * size;
            }

            int sum = 0;
            for (int j = start; j < end; j++)
            {
                sum += numbers[j];
            }

            partial_sums[i] = sum;
            shmdt(base_ptr);
            exit(0);
        }
    }

    for (int i = 0; i < M; i++) 
    {
        wait(NULL);
    }

    *final_sum = 0;
   
    for (int i = 0; i < M; i++)
    {
        *final_sum += partial_sums[i];
    }

    printf("Total Sum = %d\n", *final_sum);

    shmdt(base_ptr); 

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
