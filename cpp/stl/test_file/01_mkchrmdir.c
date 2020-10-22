/*
 * test mkdir(), chdir(), rmdir()
 *
 * */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

void t_mkchrmdir() {
    char* dir = (char*)"testdir";
    
    char path[4096] = "\0";
    
    getcwd(path, 4095);
    fprintf(stderr, "current dirctory is: %s\n", path);

    if(mkdir(dir, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH) < 0) {
        printf("mkdir failed\n");
        return;
    }
    printf("mkdir %s\n", dir);
    
    if(chdir(dir) < 0) {
        printf("chdir failed \n");
        return;
    }

    getcwd(path, 4095);
    printf("cd %s\n", path);
    
    rmdir(path);
    printf("rmdir %s\n", path);
}

int main(int argc,char *argv[]) {
    t_mkchrmdir();

    return 0;
}
