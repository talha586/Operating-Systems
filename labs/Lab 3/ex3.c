#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0)
    {
        pid_t gc1 = fork();

        if (gc1 == 0)
        {
            printf("GC1\n");
	    printf("PID= %d \n", getpid());
	    printf("PPID= %d \n", getppid());
            exit(0);
        }

        wait(NULL);
        printf("C1\n");
        printf("PID= %d \n", getpid());
        printf("PPID= %d \n", getppid());
        exit(0);
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            pid_t gc2 = fork();
            if (gc2 == 0)
            {
            	printf("GC2\n");
           	 printf("PID= %d \n", getpid());
           	 printf("PPID= %d \n", getppid());

                exit(0);
            }
            wait(NULL);

            printf("C2\n");
            printf("PID= %d \n", getpid());
            printf("PPID= %d \n", getppid());

            exit(0);
        }
        else
        {
            wait(NULL);
            wait(NULL);
            printf("P\n");
            printf("PID= %d \n", getpid());
            printf("PPID= %d \n", getppid());

        }
    }
    return 0;
}
