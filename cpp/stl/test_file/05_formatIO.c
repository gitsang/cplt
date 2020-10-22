/*
 * test format I/O: fprintf & fscanf
 *
 * fputs "aa bb 88 99" and format scanf them to 
 * str1, str2, num1, num2
 *
 * */

#include<stdio.h>
#include<stdbool.h>

void t_format() {
    FILE *fp = NULL;
    char str1[10] = {0};
    int num1 = 0;
    float num2 = 0;
    double num3 = 0;
    char ch1 = 0;

    if((fp=fopen("file1","w+")) == NULL) {
        fprintf(stderr, "file [%s] open error\n", "file1");
        return;
    }

    fprintf(fp, "%s %d %f %lf %c\n", "str1", 10, 5.2f, (double)6.3f, 'a');
    fflush(fp);
    
    rewind(fp);
    fscanf(fp, "%s %d %f %lf %c", str1, &num1, &num2, &num3, &ch1);

    printf("str1[%s],num1[%d],num2[%f],num3[%lf],ch1[%c]", str1, num1, num2, num3, ch1);

    fclose(fp);
}

int main() {

    t_format();
    
    return 0;
}
