#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork 1 failed");
        return 1;
    }

    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork 2 failed");
        return 1;
    }

    if (pid2 == 0) {

        int f = open("c_files.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (f < 0) {
            perror("Open file failed");
            exit(1);
        }

        dup2(fd[0], STDIN_FILENO);
        dup2(f, STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);
        close(f);

        execlp("grep", "grep", ".c", NULL);
        perror("execlp grep failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    return 0;
}
