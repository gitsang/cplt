#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */

/*
 * raise: parameters:
 *
 * SIGABRT  (Signal Abort) Abnormal termination, such as is initiated by the abort function.
 * SIGFPE   (Signal Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an operation resulting in overflow (not necessarily with a floating-point operation).
 * SIGILL   (Signal Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.
 * SIGINT   (Signal Interrupt) Interactive attention signal. Generally generated by the application user.
 * SIGSEGV  (Signal Segmentation Violation) Invalid access to storage: When a program tries to read or write outside the memory it is allocated for it.
 * SIGTERM  (Signal Terminate) Termination request sent to program.
 * 
 * */

sig_atomic_t signaled = 0;

void sighandler(int param) {
    signaled = param;
}

int main() {
    signal(SIGINT, sighandler);

    raise(SIGINT);

    printf("signaled is %d.\n", signaled);

    return 0;
}
