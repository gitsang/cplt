#include <stdio.h>

int main() {
    char * s = (char*)"aaaaa";
    char ** ptr;
    *ptr = (char *)s;

    /* s 为 s 的首地址*/
    printf("s = %s\n", s);
    /* %p 用于打印 s 的首地址*/
    printf("&s = %p\n", s);
    
    /* *ptr == s; 通过 ptr 一次解引用（*ptr）即可获取 s 的首地址 */
    printf("*ptr = %s\n", *ptr);

    /* *ptr 中存储的就是 s 的首地址 */
    /* ptr 中存储着存放 s 首地址的指针的地址 */
    printf("*ptr addr = %p = s addr\n", *ptr);
    
    printf("ptr addr = %p\n", ptr);

    return 0;
}
