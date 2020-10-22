/*
 * test setbuf and fflush, fsync
 * */

#include <stdio.h>  
#define SIZE 50

int main(void) {
    char buffer[BUFSIZ];
    FILE * fp1, * fp2;

    fp1 = fopen("file1","w");
    fp2 = fopen("file2","a");

    setbuf(fp1, buffer);
    fputs("This is sent to a buffered stream", fp1);
    
    /*  the data is logically part of the stream, but it 
     *  has not been writen to the device until the fflush 
     *  function is called */
    fflush(fp1);

    while(1) ;
    
    setbuf(fp2, NULL);
    fputs("This is sent to an unbuffered stream", fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
