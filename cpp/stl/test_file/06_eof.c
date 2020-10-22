/* 
 * test: what EOF means, and how to know where the file is ending.
 * 
 * how can we know end of file if EOF not exit or open a binery file.
 * 
 * what's the different between EOF and feof() and what is chearerr.
 *
 * test: ferror, perror and test how to clear error symbol
 *
 * */

#include <stdio.h>

void t_ferror() {
    FILE* fp = NULL;
    fp = fopen("file1", "wb");
    fgetc(fp);
    
    /* ferror() will return non-zero if the error indicator associated 
     * with stream is set. 
     *
     * This indicator is generally set by a previous operation on the 
     * stream that failed, and is cleared by a call to clearerr, rewind
     * or freopen.*/
    if( ferror(fp) ) {
        perror("1 Error");
        
    }
    
    clearerr(fp);
    if( ferror(fp) ) {
        perror("2 Error");
    }
    
    fgetc(fp);
    rewind(fp);
    if( ferror(fp) ) {
        perror("3 Error");
    }
    
    fgetc(fp);
    freopen("file1", "rb", fp);
    if( ferror(fp) ) {
        perror("4 Error");
    }
    fgetc(fp);
    if( ferror(fp) ) {
        perror("5 Error");
    }
    
    fclose(fp);
}

void t_feof(char* argv[]) {
    FILE* fp = NULL;
    int n = 0;

    argv[1] = (char*)"file1";
    if((fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "fopen error\n");
        return;
    }
        /* system will return EOF only when end of file or read error,
         * even if fgetc(-1), file would not end, fgetc(-1)!=EOF
         * 
         * EOF = 0xFFFFFFFF not 0xFF */
        while(fgetc(fp) != EOF) {
            n ++;
        }
        if(feof(fp)) {
            fprintf(stderr, "file size [%d]\n", n);
        }
        
        /* any of the function below will clean EOF symbol */
        clearerr(fp);
        //rewind(fp);
        //freopen("file1", "rb", fp);
        if(feof(fp)) {
            fprintf(stderr, "this sentence will not display\n");
        }
        
    fclose(fp);
}

int main(int argc, char* argv[]) {

    printf("t_ferror():\n");
    t_ferror();

    printf("t_feof():\n");
    t_feof(argv);

    return(0);
}
