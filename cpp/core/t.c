#include <iostream>
#include <stdio.h>

#include <signal.h>

/* make: g++ t.c */
using namespace std;

void t_core() {
    int i = 0;
    scanf("%d", i);
    printf("%d", i);
}

void t_core_1() {
    int* p = NULL;

    *p = 7;
    printf("%d", *p);
}

sig_atomic_t signaled = 0;

void sighandler(int param) {
    signaled = param;
    printf("sig segv");
}

int main() {
    //t_core();
    //signal(SIGSEGV, sighandler);
    t_core_1();
    
    while(1) {
    }
    return 0;
}

/*
int main() {
    //signal(SIGINT, sighandler);
    signal(SIGSEGV, sighandler);

    raise(SIGINT);

    printf("signaled is %d.\n", signaled);

    return 0;
}
*/


