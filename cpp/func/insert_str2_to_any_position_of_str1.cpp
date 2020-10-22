/* 
 * insert str2 to any position of str1
 *
 * 1 convert string to char* 
 * 2 realloc the size of ch1
 * 3 memcpy from offset
 *
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

int main() {
    std::string str1 = "aaaaa";
    std::string str2 = "12";
    char* ch1 = (char*)malloc(strlen(str1.c_str()));
    char* ch2 = (char*)malloc(strlen(str1.c_str()));
    strcpy(ch1, str1.c_str());
    strcpy(ch2, str2.c_str());
    int offset = 1;

    size_t total_len = std::max(offset + strlen(ch2), strlen(ch1));
    ch1 = (char*)realloc(ch1, total_len);
    
    memcpy(ch1+offset, ch2, strlen(ch2));
    str1 = ch1;

    std::cout << "str1 = " << str1 << std::endl;
    
    return 0;
}
