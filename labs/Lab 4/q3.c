#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>

int word_count(FILE *file_ptr)
{
    int total = 0;
    char ch;
    int word = 0;

    while ((ch = fgetc(file_ptr)) != EOF)
    {
        if (isspace(ch))
        {
    	    word = 0;
	}

        else if (!word)
        {
            total++;
            word = 1;
        }
    }
    return total;
}

int main(int argc, char *argv[])
{
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    
    pid_t pid1, pid2;
    int fd1, fd2;
    int count1 = 0, count2 = 0;

    if (mkfifo(fifo1, 0666) == -1 || mkfifo(fifo2, 0666) == -1) 
    {
        perror("mkfifo error");
        return 1;
    }

    fd1 = open(fifo1, O_RDONLY);
    fd2 = open(fifo2, O_RDONLY);

    pid1 = fork();
    if (pid1 < 0)
    { 
	 perror("fork1");
	 exit(1);
    }

    if (pid1 == 0)
    {
        FILE *fp = fopen(argv[1], "r");
       
	 if (!fp)
	{
	    exit(1);
	}

        int result = word_count(fp);
        fclose(fp);

        int write_fd = open(fifo1, O_WRONLY);
        write(write_fd, &result, sizeof(result));
        close(write_fd);
        exit(0);
    }

    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork2");
        exit(1); 
    }

    if (pid2 == 0)
    {
        FILE *fp = fopen(argv[1], "r");
        if (!fp)
	{
            exit(1);
	}

        int result = word_count(fp);
        fclose(fp);

        int write_fd = open(fifo2, O_WRONLY);
        write(write_fd, &result, sizeof(result));
        close(write_fd);
        exit(0);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    read(fd1, &count1, sizeof(count1));
    read(fd2, &count2, sizeof(count2));

    close(fd1);
    close(fd2);

    printf("Total Words: %d\n", count1 + count2);

    unlink(fifo1);
    unlink(fifo2);
}
