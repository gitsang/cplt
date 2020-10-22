#include <stdio.h>      /* printf */
#include <stddef.h>     /* offsetof */
#include <string.h>

struct foo {
    char a;
    char b[10];
    char c;
};

int t_offsetof() {
    printf ("offsetof(struct foo,a) is %d\n",(int)offsetof(struct foo,a));
    printf ("offsetof(struct foo,b) is %d\n",(int)offsetof(struct foo,b));
    printf ("offsetof(struct foo,c) is %d\n",(int)offsetof(struct foo,c));

    return 0;
}

void t_val() {
    char str[] = "Hello world!";
    char *p1 = str;
    char *p2 = str + strlen(str);
    ptrdiff_t pd = p2 - p1;
    printf("p2 - p1 = %d\n", pd);

    wchar_t wc = 1;
    printf("sizeof(wc) = %d\n", sizeof(wc));
}

int main() {
    t_offsetof();
    t_val();

    return 0;
}
