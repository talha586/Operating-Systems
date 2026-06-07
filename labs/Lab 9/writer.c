#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_data.h"

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    
    
    ftruncate(shm_fd, sizeof(struct shared_struct));


    struct shared_struct *ptr = mmap(0, sizeof(struct shared_struct), 
                                     PROT_WRITE, MAP_SHARED, shm_fd, 0);

    ptr->id = 101;
    strncpy(ptr->message, "Hello from Writer!", 32);

    munmap(ptr, sizeof(struct shared_struct));
    close(shm_fd);

    printf("Writer: Data written to shared memory.\n");
    return 0;
}
