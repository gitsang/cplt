#include <stdio.h>
#include <string.h>
#include <errno.h>

void t_strcat() {
    /* test: 
     *      strcat(); strncat();
     *      strstr();
     * */

    printf("\n");
    char str[80];
    strcpy(str, "aaaa ");
    /* append a copy of "bbbb " to "aaaa " */
    strcat(str, "bbbb ");
    /* append a copy of "cccc" to "aaaa " */
    strncat(str, "cccccccccc", 4);
    puts(str);

    char* pch = strstr (str, "bbbb");
    strncpy (pch, "xxxx", 4);
    puts(str);
}
void t_strchr() {
    /* test: 
     *      strchr(); strrchr();
     * */

    printf("\n");
    char str[] = "adgafafsfsdgageh";
    char* pch;
    printf("Looking for the 's' character in \"%s\"...\n",str);
    /* Return a pointer to the first occurrence of character in the C string str */
    pch = strchr(str, 's');
    while(pch != NULL) {
        printf("found at %d\n", pch-str+1);
        pch = strchr(pch+1, 's');
        /* not found return NULL */
    }

    pch = strrchr(str, 's');
    printf("last 's' found at %d\n", pch-str+1);
}
void t_strcmp() {
    /* test:
     *      strcmp(); strncmp(); memcmp();
     * */

    printf("\n");
    char str1[10] = "aabb";
    char str2[10] = "aabbgggd";
    
    printf("strcmp return : %d\n", strcmp(str1, str2));
    printf("strncmp 4 return : %d\n", strncmp(str1, str2, 4));
    /* same as strcmp, but strcoll will compare string with LC_COLLATE (environment variety) */
    printf("strcoll return : %d\n", strcoll(str1, str2));
    /* unlike strcmp, memcpy does not stop comparing after finding a null character. */
    printf("memcmp 4 return : %d\n", memcmp(str1, str2, 4));
    
}
void t_strerror() {
    /* test:
     *      strerror();
     * */

    printf("\n");
    FILE* fp = NULL;
    fp = fopen("unexist", "r");
    if(fp == NULL) {
        printf("error to fopen %s\n", strerror(errno)); 
    }
}
void t_str_match() {
    /* test:
     *      strcspn(); strspn();
     *      strpbrk(); strtok();
     * */

    printf("\n");
    char str[] = "fa3fa9sg";
    char str2[] = "269aaa9999";
    char key[] = "1234567890";
    /* strcspn() will find the first position of char that match key */
    /* not match will return lengths of str */
    printf("the first char in str that match key is at %d\n", strcspn(str, key) + 1);
    /* strspn() 返回从头开始符合key的数量 */
    printf("str has %d char that match key from initial portion\n", strspn(str, key));
    printf("str2 has %d char that match key from initial portion\n", strspn(str2, key));
    
    /* not match - will return NULL */
    char* pch = strpbrk(str, key);
    printf ("first match %c\n", *pch);
    pch = strpbrk(pch+1, key);
    printf ("second match %c\n", *pch);

    char str3[] = "- This, a sample string.";
    /* 将str以delim（参数2）分解为子串 */
    pch = strtok(str3, " ,.-");
    /* not match - will return NULL */
    while(pch != NULL) {
        printf("%s\n", pch);
        /* 再次调用要把第一个参数设为NULL */
        pch = strtok(NULL, " ,.-");
    }
}
void t_strxfrm() {
    /* size_t strxfrm(char *dest, const char *src, size_t n) 
     * 根据程序当前的区域选项中的 LC_COLLATE 来转换字符串 src 的前 n 个字符，
     * 并把它们放置在字符串 dest 中 */ 

    printf("\n");
    char dest[20]="\0";
    char src[20];
    int len;
    
    strcpy(src, "wwwwwww");
    len = strxfrm(dest, src, 20);
    /* same as strncpy */
    printf("string \"%s\" length = %d\n", dest, len);
}

int main() {
    t_strcat();
    t_strchr();
    t_strcmp();
    t_strerror();
    t_str_match();
    t_strxfrm();

    return 0;
}
