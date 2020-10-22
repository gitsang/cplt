/*
 * test fgets(), fputs()
 * use to append content to file
 *
 * */

#include<stdio.h> 

#define SIZE 512

void t_append(int argc, char* argv[]) {
    if(argc < 3) {
        fprintf(stderr, "usage: ./append file1 file2");
        return;
    }

    FILE* fp1 = NULL;
    FILE* fp2 = NULL;
    char buffer[SIZE] = {0};

    if((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "open file [%s] failed.\n", argv[1]);
        return;
    }    

    if((fp2 = fopen(argv[2], "a")) == NULL) {
        fprintf(stderr, "open file [%s] failed.\n", argv[2]);
        fclose(fp1);
        return;
    }
    
    while(fgets(buffer, SIZE, fp1) != NULL) {
        fputs(buffer, fp2);
    }
    
    fclose(fp1);
    fclose(fp2);
}

int main(int argc,char* argv[]) {
    t_append(argc, argv);

    return 0;
}
