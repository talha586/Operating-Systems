#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<wait.h>
int main(int argc,char* argv[])
{
	int val=atoi(argv[1]);
	pid_t pid1,pid2;
	int pipe1[2],pipe2[2];

	if(pipe(pipe1)==-1 || pipe(pipe2)==-1)
	{
		perror("Error in creation pipe");
		return 1;
	}

	pid1=fork();
	if(pid1==0)
	{
		int sum=0;
		close(pipe1[0]);
		close(pipe2[0]);
		close(pipe2[1]);
		for(int i=0;1<val/4;i++)
		{
			if(val%i==0)
			{
				sum+=i;
			}
		}
		write(pipe1[1],&sum,sizeof(int));
		close(pipe1[1]);
		exit(0);
	}

	pid2=fork();
	if(pid2==0)
	{
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		int sum=0;
		for(int i=val/4;i<=val/2;i++)
		{
			if(val%i==0)
			{
				sum+=i;
			}
		}
		write(pipe2[1],&sum,sizeof(int));
		close(pipe2[1]);
		exit(0);
	}

	int x,y;
	read(pipe1[0],&x,sizeof(int));
	read(pipe2[0],&y,sizeof(int));

	wait(NULL);
	wait(NULL);

	if(x+y==val)
	{
		printf("True");
	}

	else
	{
		printf("False");
	}
return 0;
}
