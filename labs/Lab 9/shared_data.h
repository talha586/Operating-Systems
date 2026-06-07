#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#define SHM_NAME "/my_shared_memory"

struct shared_struct {
    int id;
    char message[32];
};

#endif
