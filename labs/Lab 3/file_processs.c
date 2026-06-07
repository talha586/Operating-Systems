#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	pid_t pid=fork();
	FILE *fp;
	int ch;
	if(pid==0)
	{
		printf("Child Executing\n");
		fp =fopen("sample.txt","w");
		while((ch=getchar())!=EOF)
		{
			putc(ch,fp);
		}
		fclose(fp);
		exit(0);
	}
	else
	{
		wait(NULL);
		fp =fopen("sample.txt","r");
		while((ch=getc(fp))!=EOF)
		{
			putchar(ch);
		}
		fclose(fp);
	}
return 0;
}
