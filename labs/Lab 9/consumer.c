
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_data.h"

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    struct shared_data *ptr = mmap(0, sizeof(struct shared_data), PROT_READ, MAP_SHARED, shm_fd, 0);

    int last_seen = -1;
    while (!ptr->done) {
        if (ptr->counter != last_seen) {
            printf("Consumer: Read counter value: %d\n", ptr->counter);
            last_seen = ptr->counter;
        }
        usleep(100000);
    }

    printf("Consumer: Final counter value received: %d\n", ptr->counter);

    munmap(ptr, sizeof(struct shared_data));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
