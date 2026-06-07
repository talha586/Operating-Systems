#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() 
{
const char *filepath = "data.txt";
const char *append_text = " - Updated!";

int fd = open(filepath, O_RDWR);
if (fd < 0) 
{ 
    perror("open"); 
    return 1; 
}

struct stat st;
stat(filepath, &st);
size_t original_size = st.st_size;
size_t new_size = original_size + strlen(append_text);

ftruncate(fd, new_size);

char *map = mmap(NULL, new_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (map == MAP_FAILED) 
{ 
    perror("mmap"); 
    return 1; 
}

printf("Original content: %.*s\n", (int)original_size, map);

memcpy(map + original_size, append_text, strlen(append_text));

printf("Updated content: %.*s\n", (int)new_size, map);

munmap(map, new_size);
close(fd);

}