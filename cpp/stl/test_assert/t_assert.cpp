#include <stdio.h>
#include <assert.h>

void t_assert() {
    int a = 1;
    assert(a > 10);
    printf("no error a = %d\n", a);
}

int main () {
    t_assert();

    return 0;
}
