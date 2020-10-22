#include<stdio.h> 

int main(int argc,char *argv[]) 
{
    FILE* fp = NULL;
    
    /* FILE* fopen(char* path, char* mode) */
    fp = fopen("file1", "r+");
    if(fp == NULL) {
        fprintf(stderr, "open file [%s] failed.\n", "file1");
        return 0;
    }else {
        fprintf(stderr, "open file [%s] success.\n", "file1");
    }
    
#if 0
    /* int fgetc(FILE* fp) */
    /* int fputc(int ch, FILE* fp) */
    FILE* fp2 = fopen("file2", "w+");
    int ch = fgetc(fp);
    while(ch!=EOF) {
        putchar(ch);
        fputc(ch, fp2);
        ch = fgetc(fp);
    }
    fclose(fp2);
#endif
    
#if 0
    /* size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* fp) */
    char* buffer = (char*)"abcdefghij";
    if(fwrite(buffer, strlen(buffer), 1, fp)) {
        fprintf(stderr, "fwrite success.\n");
    }else {
        fprintf(stderr, "fwrite error.\n");
    }
#endif

#if 0
    /* size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp) */
    char buffer[10];
    
    fseek(fp, 0, SEEK_SET);
    int res1 = fread(buffer, 1, sizeof(buffer), fp);
    fprintf(stderr, "fread success: %s [res:%d]\n", buffer, res1);
    
    fseek(fp, 0, SEEK_SET);
    int res2 = fread(buffer, sizeof(buffer), 1, fp);
    fprintf(stderr, "fread success: %s [res:%d]\n", buffer, res2);
    /* if buffer size > file size will return 0(error) */
#endif
     
    /* int fclose(FILE* fp) */
    if(fclose(fp) == EOF) {
        fprintf(stderr, "close file [%s] failed.\n", "file1");
    }else {
        fprintf(stderr, "close file [%s] success.\n", "file1");
    }
    
    return 0;
}
