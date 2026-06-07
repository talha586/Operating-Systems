
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_data.h"

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct shared_data));
    struct shared_data *ptr = mmap(0, sizeof(struct shared_data), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    ptr->counter = 0;
    ptr->done = 0;

    for (int i = 1; i <= 10; i++) {
        ptr->counter = i;
        printf("Producer: Updated counter to %d\n", ptr->counter);
        sleep(1);
    }

    ptr->done = 1;

    munmap(ptr, sizeof(struct shared_data));
    close(shm_fd);

    printf("Producer: Task complete.\n");
    return 0;
}
s
