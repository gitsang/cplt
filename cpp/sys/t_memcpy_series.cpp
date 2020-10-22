#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    char* content_;
    char* content = "123456789";
    int offset = 0;

    content_ = new char(strlen(content));
    memcpy(content_+offset, content, strlen(content));
    /* in simple program it can work properly
     * but in other case, this can be wrong 
     * memcpy may copy more than strlen(content)
     * though you have set the length to restrict it */

    fprintf(stderr, "strlen(content_) = %d\ncontent_ = %s\n", strlen(content_), content_);
}
