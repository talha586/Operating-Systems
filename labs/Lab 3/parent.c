#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int size,char* arr[])
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("Child processing %s \n",arr[1]);
		execlp(arr[1],arr[1],NULL);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("Parent Process \n");
	}
return 0;
}
