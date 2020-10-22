#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    clock_t time_used;

    pid_t childpid = fork();

    FILE* fp = NULL;
    fp = fopen("tmp.dat", "w+");
    if(fp == NULL) {
        perror("failed to open\n");
        return -1;
    }

    if(childpid == 0) { // child read
        for(int i = 0; i < 10000; i++) {
            usleep(1000000);
            fseek(fp, 0, SEEK_SET);
            char tmp[10000] = "\0";
            size_t res = fread(tmp, 1, 9999, fp);
            if(ferror(fp)) {
                perror("read error");
            }

            printf("buf: %s, res: %d\n", tmp, res);
        }
    }else if(childpid > 0){ // father write
        char ch = 'a';
        for(int i = 0; i < 10000; i++) {
            usleep(1000000);
            if (ch > 'z') {
                ch = 'a';
            }
            fwrite(&ch, 1, 1, fp);
            fflush(fp);
            ch ++;
        }
    }
    fclose(fp);

    return 0;
}
