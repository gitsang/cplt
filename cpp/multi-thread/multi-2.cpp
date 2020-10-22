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

    if(childpid == 0) { // child
        char ch = 0;
        
        fseek(fp, 0, SEEK_SET);
        for(int i = 0; i < 10000; i++) {
            ch = fgetc(fp);
            printf("%d:%c\t", i, ch);
        }

    }else if(childpid > 0){ // father
        char ch = 'a';

        for(long i = 0; i < 10000; i++) {
            fputc(ch, fp);
        }
    }
    fclose(fp);

    return 0;
}
