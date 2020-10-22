/* using vector to storage string and separate it
 * each block have 10 byte
 *
 * when write content to vector:
 * program can auto manage them to the correct block
 * when read it:
 * use offset/10 to find the block number,
 * use offset%10 to find the offset in block
 */

#include <iostream>
#include <vector>
#include <cstring>
#define SIZE 10
using namespace std;

int main() {
    char* data1 = new char[26]; 
    strcpy(data1, (char*)"aaaaaaaaaabbbbbbbbbb12345");
    /*
                             5:offset
       index [0][1][2][3][4][5][6][7][8][9][A]
      *[0]->  a  a  a  a  a  a  a  a  a  a
      *[1]->  b  b  b  b  b  b  b  b  b  b
      *[2]->  1  2  3  4  5                     current_block:2
    */
    char* data2 = new char[18]; 
    strcpy(data2, (char*)"cccccccccc7777777");
    /*
                    2:offset
       index [0][1][2][3][4][5][6][7][8][9][A]
      *[0]->  a  a  a  a  a  a  a  a  a  a
      *[1]->  b  b  b  b  b  b  b  b  b  b
      *[2]->  1  2  3  4  5  c  c  c  c  c 
      *[3]->  c  c  c  c  c  7  7  7  7  7
      *[4]->  7  7                              current_block:4
    */

    vector<char*> vec;

    int current_block = 0;
    int offset = 0;
    int data_offset = 0;
    
    int len = 0;
    
    /* copy data1 to vector */
    while(data_offset < strlen(data1)) {
        if(vec.size() < current_block+1) {
            vec.push_back(new char[SIZE]);
        }
        len = min(SIZE-offset, (int)strlen(data1)-data_offset);
        memcpy(vec[current_block]+offset, data1+data_offset, len);
        data_offset += len;
        offset += len;

        if(offset >= SIZE) {
            offset = 0;
            current_block ++;
        }
    }

    data_offset = 0;

    /* copy data2 to vector */
    while(data_offset < strlen(data2)) {
        if(vec.size() < current_block+1) {
            vec.push_back(new char[SIZE]);
        }
        len = min(SIZE-offset, (int)strlen(data2)-data_offset);
        memcpy(vec[current_block]+offset, data2+data_offset, len);
        data_offset += len;
        offset += len;

        if(offset >= SIZE) {
            offset = 0;
            current_block ++;
        }
    }

    return 0;
}
