#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{

    int fd1 = open("input.txt", O_RDONLY);
    if (fd1 < 0)
    {
        exit(1);
    }

    dup2(fd1, 0);
    close(fd1);

    int fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd2 < 0)
    {
        exit(1);
    }

    dup2(fd2, 1);
    close(fd2);

    int ch;
    int sum = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch >= '0' && ch <= '9')
        {
            sum += (ch - '0');
        }
    }
    return 0;

}
