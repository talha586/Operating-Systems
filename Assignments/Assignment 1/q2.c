#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void run_command(char **args, char *input_file, char *output, int append)
{
    pid_t pid = fork(); 

    if (pid == 0)
    { 

        if (input_file != NULL)
        {
            int fd1 = open(input_file, O_RDONLY);

            if (fd1 >= 0)
            {
                dup2(fd1, 0);
                close(fd1);
            }
        }

      
        if (output != NULL)
        {
            int fd2;
            if (append == 1)
            {
               
                fd2 = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else
            
          
                fd2 = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }

            if (fd2 >= 0) 
            {
                dup2(fd2, 1);
                close(fd2);;
            }
        }

        execvp(args[0], args); 
        exit(1); 
    }

    else
    {
        wait(NULL); 
    }
}

int main()
 {
    char input[1024];
    char *args[64];
    char *input_file = NULL;
    char *output = NULL;
    int append = 0;
    int i = 0

         while (1) 
        {

        printf("TALHA> ");

        if (fgets(input, 1024, stdin) == NULL)
	{
		 break;
	}

        input[strcspn(input, "\n")] = 0; 

        if (strcmp(input, "exit") == 0)
	{	
		 break;
	}

 

        char *token = strtok(input, " ");
       
	 while (token != NULL)
	 {
            if (strcmp(token, "<") == 0)
	    {
                input = strtok(NULL, " ");
            }
            else if (strcmp(token, ">") == 0) 
            {
                output = strtok(NULL, " ");
                append = 0;
            
            else if (strcmp(token, ">>") == 0) 
            {
                output = strtok(NULL, " ");
                append = 1;;
            }
 
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        if (args[0] == NULL)
	{
		continue;
	}

        if (strcmpa(args[0], "cd") == 0) 
	{
            if (args[1] != NULL)
	    {	
		 chdir(args[1]);
	    }
        } 

        else
        {
            run_command(args, input, output, append);;
        }
    }
}
