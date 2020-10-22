/*
 * isalnum      Check if character is alphanumeric
 * isalpha      Check if character is alphabetic
 * isblank      Check if character is blank
 * iscntrl      Check if character is a control character
 * isdigit      Check if character is decimal digit
 * isgraph      Check if character has graphical representation
 * islower      Check if character is lowercase letter
 * isprint      Check if character is printable
 * ispunct      Check if character is a punctuation character
 * isspace      Check if character is a white-space
 * isupper      Check if character is uppercase letter
 * isxdigit     Check if character is hexadecimal digit
 * */


#include <stdio.h>
#include <ctype.h>

void t_ctype() {

    if(isalnum((int)'c')) {
        printf("'c' is alphanumeric.\n");
    }else {
        printf("'c' is not alphanumeric.\n");
    }
    
    if(isalpha((int)'3')) {
        printf("'3' is alphabetic.\n");
    }else {
        printf("'3' is not alphabetic.\n");
    }
    
    if(iscntrl((int)'\n')) {
        printf("'\\n' is cntrl.\n");
    }else {
        printf("'\\n' is not cntrl.\n");
    }
    
    if(ispunct((int)'?')) {
        printf("'?' is punctuation character.\n");
    }else {
        printf("'?' is not punctuation character.\n");
    }

    if(isblank((int)' ')) {
        printf("' ' is blank.\n");
    }else {
        printf("' ' is not blank.\n");
    }

    if(isgraph((int)' ')) {
        printf("' ' is graph.\n");
    }else {
        printf("' ' is not graph.\n");
    }
    
    if(isprint((int)' ')) {
        printf("' ' is printable.\n");
    }else {
        printf("' ' is not printable.\n");
    }

    if(isspace((int)' ')) {
        printf("' ' is space.\n");
    }else {
        printf("' ' is not space.\n");
    }

    if(isdigit((int)'9')) {
        printf("'9' is decimal digit.\n");
    }else {
        printf("'9' is not decimal digit.\n");
    }
    
    if(isxdigit((int)'A')) {
        printf("'A' is hexadecimal digit.\n");
    }else {
        printf("'A' is not hexadecimal digit.\n");
    }

    if(islower((int)'A')) {
        printf("'A' is lowercase.\n");
    }else {
        printf("'A' is not lowercase.\n");
    }
    
    if(isupper((int)'A')) {
        printf("'A' is uppercase.\n");
    }else {
        printf("'A' is not uppercase.\n");
    }

    putchar(tolower('B'));
    putchar(toupper('b'));
}

int main() {
    t_ctype();

    return 0;

}
