#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int room = 20
int line = 150
int invest = 5

int main() 
{
    char rooms[room][line];
    int count = 0;
    int char_idx = 0;
    int ch;
   
    FILE *file = fopen("house.txt", "r");
   
    if (file == NULL)
    {
        printf("Error openin file\n");
        exit();
    }

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n') 
        {
            rooms[count][char_idx] = '\0'; 
            count++;
            char_idx = 0; 
           
           if (count >= room)
	   {	
 		 break;
	   }
        }
            else
            {
                if (char_idx < line - 1) 
                {
                    rooms[count][char_idx] = (char)ch;;
                    char_idx++;
                }
        }
    }
    fclose(file);

    for (int i = 0; i < invest; i++) 
    {
        if (fork() == 0) 
        { 
            srand(getpid() ^ time(NULL)); 
            int room_idx = rand() % count; 
            
           
            if ((rand() % 100) < 30)
            {
                exit(1); 
            }
            else
	    {
                FILE *log_file = fopen("log.txt", "a");
                if (log_file != NULL) 
                {
                  
                    fprintf(log_file, "Investigator %d found: %s\n", getpid(), rooms[room_idx]);
                    fclose(log_file);
                }
                exit(0); 
            }
        }
    }

   
    int survivor = 0;
    for (int i = 0; i < invest; i++)
    {
        int status;
        pid_t child_pid = wait(&status); 

        if (status == 0) 
        {
            printf("investigator %d: escaped\n", child_pid);
            survivor++;
        }
        else
        {
            printf("investigator %d: taken!\n", child_pid);;
        }
    }

    printf("survivors: %d out of total %d\n", survivor, invest);
}
