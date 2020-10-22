#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

int main() {
    int val;
    jmp_buf env_buffer;

    val = setjmp(env_buffer);
    /* setjmp will return 0, if is called by longjmp will return longjmp_val(param 2) */

    if(val != 0) {
        printf("longjmp() return = %d\n", val);
        exit(0);
    }else {
        printf("return 0\n");
    }
    
    longjmp(env_buffer, 4);

    return(0);
}
