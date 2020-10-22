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

    if(childpid == 0) { // child read
        for(int i = 0; i < 1000; i++) {
            fp = fopen("tmp.dat", "w+");
            if(fp == NULL) {
                perror("failed to open");
                return -1;
            }

            usleep(1000000);
            fseek(fp, 0, SEEK_SET);
            char buf[1000] = {0};
            size_t res = fread(buf, 1, 999, fp);
            if(ferror(fp)) {
                perror("read error");
            }
            printf("buf: %s, res: %d\n", buf, res);

            fclose(fp);
        }
    
    }else if(childpid > 0){ // father write
        char ch = 'a';
        fp = fopen("tmp.dat", "w+");
        if(fp == NULL) {
            perror("failed to open");
            return -1;
        }

        for(int i = 0; i < 1000; i++) {

            if (ch > 'z') {
                ch = 'a';
            }
            usleep(1000000);
            fwrite(&ch, 1, 1, fp);
            fflush(fp);
            ch ++;

        }

        fclose(fp);
    }


    if(fp != NULL) {
        fclose(fp);
    }

    return 0;
}
