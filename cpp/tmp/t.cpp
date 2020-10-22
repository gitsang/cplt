#include <stdio.h>
#include <iostream>

int main() {
    //char buf[256] = {0};
    char* buf[1000000] = {0};
    printf("111\n");

    FILE* fl = fopen("txt", "rb+");
    fseek(fl, 0, SEEK_END);
    printf("222\n");

    uint64_t len = ftell(fl);

    try{
        fseek(fl, 0, SEEK_SET);
        uint64_t rlen = fread(buf, 10, len, fl);
        printf("len: %d, rlen: %d \n", len, rlen);
    }
    catch(const std::exception &e) {
        printf("%s\n", e); 
    }

    printf("len: %d, rlen: %d \n", len, rlen);

    return 0;
}
