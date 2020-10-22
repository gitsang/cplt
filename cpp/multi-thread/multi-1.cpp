#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    clock_t time_used;

    int times = argc > 1 ? atoi(argv[1]) : 10000;
    int fd;

    pid_t childpid = fork();

    fd = open("tmp.dat", O_WRONLY | O_CREAT | O_APPEND, 0666);

    if(fd < 0) {
        perror("failed to open\n");
        return -1;
    }

    if(childpid > 0) {
        char* buf = (char*)malloc(times);
        for(int i = 0; i < times; i++) {
            buf[i] = 'a';
        }
        buf[times] = '\n';
        for(int i = 0; i < 10; i++) {
            write(fd, buf, strlen(buf));
        }
    }else {
        char* buf = (char*)malloc(times);
        for(int i = 0; i < times; i++) {
            buf[i] = 'b';
        }
        buf[times] = '\n';
        for(int i = 0; i < 10; i++) {
            write(fd, buf, strlen(buf));
        }
    }
    close(fd);

    return 0;
}
