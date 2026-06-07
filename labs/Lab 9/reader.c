#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_data.h"

int main() {

    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);

    struct shared_struct *ptr = mmap(0, sizeof(struct shared_struct), 
                                     PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("Reader: ID = %d\n", ptr->id);
    printf("Reader: Message = %s\n", ptr->message);

    munmap(ptr, sizeof(struct shared_struct));
    close(shm_fd);
    shm_unlink(SHM_NAME); 

    return 0;
}
