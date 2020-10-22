#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#include "shmnode.h"

int main() {
    int running = 1;
    void *shm = NULL;
    struct shmnode *sn;
    int shmid;
    int ipc_key = 1234;

    shmid = shmget((key_t)ipc_key, sizeof(struct shmnode), 0666|IPC_CREAT);
    if(shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shm = shmat(shmid, 0, 0);
    if(shm == -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shm);

    sn = (struct shmnode*)shm;

    while(running) {
        printf("sn->pos = %d\n", sn->pos);
        sleep(1);
        if(sn->pos >= 10) {
            running = 0;
        }
    }

    if(shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    
    if(shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    sleep(1);
    puts("exit success\n");
    exit(EXIT_SUCCESS);

    return 0;
}

