#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#include "shmnode.h"

int main() {
    int runing = 1;
    void* shm = NULL;
    struct shmnode* sn = NULL;
    int shmid;
    int ipc_key = 1234;

    shmid = shmget((key_t)ipc_key, sizeof(struct shmnode), 0666|IPC_CREAT);
    if(shmid == -1) {
        fprintf(stderr, "shmget fail\n");
        exit(EXIT_FAILURE);
    }
    
    shm = shmat(shmid, (void*)0, 0);
    if(shm == -1) {
        fprintf(stderr, "shmat fail\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory sttached at %X\n", (int)shm);

    sn = (struct shmnode*)shm;
    sn->pos = 1;

    while(runing) {
        sn->pos += 1;
        sleep(1);
        if(sn->pos >= 10) {
            runing = 0;
        }
    }

    if(shmdt(shm) == -1) {
        fprintf(stderr, "shmdt fail\n");
        exit(EXIT_FAILURE);
    }

    sleep(1);
    puts("exit success\n");
    exit(EXIT_SUCCESS);

    return 0;
}

