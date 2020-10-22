/* 
 * test file read and write
 * test fopen, fwrite, fread, fclose
 *
 * */

#include<stdio.h> 

void t_file_read_and_write() {
    FILE* fp = NULL;
    
    /* FILE* fopen(char* path, char* mode) */
    fp = fopen("file1", "w+");
    if(fp == NULL) {
        fprintf(stderr, "open file [%s] failed.\n", "file1");
        return;
    }
    
    /* size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* fp) */
    char content[] = "fwr.c: this is file read and write content.";
    int res = fwrite(content, 1, sizeof(content)/sizeof(char), fp);
    if(res == sizeof(content)/sizeof(char)){
        fprintf(stderr, "fwrite success, write %d bytes\n", res);
    }else {
        fprintf(stderr, "fwrite error, write %d bytes\n", res);
        fclose(fp);
        return;
    }

    /* size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp) */
    char buffer[50] = {0};
    
    fseek(fp, 0, SEEK_SET);
    int res1 = fread(buffer, 1, sizeof(buffer), fp);
    fprintf(stderr, "fread success: %s [res:%d]\n", buffer, res1);
    
    fseek(fp, 0, SEEK_SET);
    int res2 = fread(buffer, sizeof(buffer), 1, fp);
    fprintf(stderr, "fread success: %s [res:%d]\n", buffer, res2);
     
    /* int fclose(FILE* fp) */
    if(fclose(fp) == EOF) {
        fprintf(stderr, "close file [%s] failed.\n", "file1");
    }
}

int main(int argc,char *argv[]) {
    t_file_read_and_write();

    return 0;
}
