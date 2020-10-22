#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
 
/*
union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *arry;
};

struct sembuf{
    short sem_num; // 除非使用一组信号量，否则它为 0
    short sem_op;  // -1 等待 P(sv); +1 发送 V(sv)
    short sem_flg; // 通常为 SEM_UNDO ，使操作系统跟踪信号，并由系统自动释放
};
*/
 
static int sem_id = 0;

static int set_semvalue() {
    union semun sem_union;
    sem_union.val = 1;
    /* int semctl(int sem_id, int sem_num, int command, ...) 
     * command 常为：SETVAL(通过第四个参数 union semun 设置)
     *               IPC_RMID(删除sem_id)
     */
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        return 0;
    }
    return 1;
}
 
/* 删除信号量 */
static void del_semvalue() {
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) {
        fprintf(stderr, "Failed to delete semaphore\n");
    }
}
 
/* 等待：申请资源 */
static int semaphore_p() {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;//P()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p failed\n");
        return 0;
    }
    return 1;
}
 
/* 发送：释放资源 */
static int semaphore_v() {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v failed\n");
        return 0;
    }
    return 1;
}
 
int main(int argc, char *argv[]) {
    char message = 'X';
    int i = 0;
    /* int semget(key_t key, int nsems, int semflg) 
     * 根据 key 返回 sem_id
     */
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
 
    if (argc > 1) {
        if (!set_semvalue()) {
            fprintf(stderr, "Failed to initialize semaphore\n");
            exit(EXIT_FAILURE);
        }
        message = argv[1][0];
        sleep(2);
    }
 
    for (i = 0; i < 10; ++i) {
        /* 进入临界区 */
        if (!semaphore_p()) {
            exit(EXIT_FAILURE);
        }
 
        printf("%c", message);
        fflush(stdout);

        sleep(rand() % 3);
 
        printf("%c", message);
        fflush(stdout);
 
        /* 离开临界区 */
        if (!semaphore_v()) {
            exit(EXIT_FAILURE);
        }

        sleep(rand() % 2);
    }
 
    sleep(10);
    printf("\n%d - finished\n", getpid());
 
    if (argc > 1) {
        sleep(3);
        del_semvalue();
    }
    exit(EXIT_SUCCESS);
}
 
