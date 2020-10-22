#include <iostream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void sys_rm() {
    std::string filename = "file";
    int pos1 = 4;
    int pos2 = 8;

    char cmd[256];
    snprintf(cmd, 256, "rm `ls | grep \"%s\" | grep -v \"%s_00%d\" | grep -v \"%s_00%d\"` -fr",
             filename.c_str(), filename.c_str(), pos1, filename.c_str(), pos2);
    
    fprintf(stdout, "%s\n", cmd);
    system(cmd);
}

void sys_touch() {
    char cmd[256];
    strcpy(cmd, "touch file_{001..999}.a");
    fprintf(stdout, "%s\n", cmd);
    system(cmd);
    //system("ls");
}

int main() {
    // process start
    sys_touch();
    sleep(1);
    sys_rm();
    // process end
    sleep(1);

    return 0;
}
