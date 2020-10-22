
#include <stdio.h>
#include <string.h>

void t_memchr() {
    char* pch = NULL;
    char str[] = "Example string";

    pch = (char*)memchr(str, 'p', strlen(str));
    /* return pointer to the first occurrence of value */
    if(pch!=NULL) {
        printf ("'p' found at position %d.\n", pch-str+1);
    }else {
        printf ("'p' not found.\n");
    }
}
void t_memcmp() {
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";

    int n = memcmp(buffer1, buffer2, sizeof(buffer1));
    /* greater return >0, less return <0, same return =0 */

    if(n > 0) {
        printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
    }else if(n < 0) {
        printf("'%s' is less than '%s'.\n",buffer1,buffer2);
    }else {
        printf("'%s' is the same as '%s'.\n",buffer1,buffer2);
    }
    printf("\t%d\n", n);
}
void t_memmove() {
    char str[] = "memmove can be very useful......";
    memmove(str+20, str+15, 11);
    /* memmove str[15, 15+11] to str[20, 20+11] */
    puts(str);
}

int main() {
    t_memchr();
    t_memcmp();
    t_memmove();

    return 0;
}
