/*
 * test fgetc(), fputc() and EOF
 * use to copy file
 *
 * */

#include<stdio.h> 

#define SIZE 512

void t_copyfile(int argc, char* argv[]) {
    if(argc < 3) {
        fprintf(stderr, "usage: cp file1 file2\n"); 
        return;
    }

    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    if((fp1 = fopen(argv[1], "r")) == NULL) { 
        fprintf(stderr, "open file [%s] failed\n", argv[1]);
        return; 
    }    
    if((fp2 = fopen(argv[2], "w")) == NULL) { 
        fprintf(stderr, "open file [%s] failed\n", argv[2]);
        fclose(fp1);
        return; 
    }

    char ch = fgetc(fp1);
    while(ch!=EOF) {
        fputc(ch, fp2);
        ch = fgetc(fp1);
    }
     
    fclose(fp1);
    fclose(fp2);

}

int main(int argc, char *argv[]) {
    t_copyfile(argc, argv);

    return 0;
}
