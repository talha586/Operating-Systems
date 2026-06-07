#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);
        close(fd);
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        exit(0);
    }
    else
    {
        wait(NULL);
        FILE *fp = fopen("output.txt", "r");
        int ch;
        while ((ch = getc(fp)) != EOF)
	{
            putchar(ch);
        }

        fclose(fp);
    }
    return 0;
}
