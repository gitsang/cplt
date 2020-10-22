/*
 * test: vector iterator erase
 * 30,2,30,90,30,88,30
 * erase all element in one time iterate
 *
 * vector {1, 39, 923, 23902, 238904, 489582}
 * use iterator and std::find to fine 489582
 * */

#include<iostream>
#include<vector>
#include<algorithm>

void del_vec() {
    int arr[7] = {30, 2, 30, 90, 30, 88, 30};
    std::vector<int> vec(arr, arr+7);

    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ) {
        if(*it == 30) {
            std::cout << "delete " << *it << std::endl;
            it = vec.erase(it);
        }else {
            it ++;
        }
    }
}

void find_vec() {
    int arr[6] = {1, 39, 923, 23902, 238904, 489582};
    std::vector<long> vec(arr, arr+6);

    for(std::vector<long>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }
    for(std::vector<long>::iterator it = vec.begin(); it != vec.end(); it++) {
        if(*it == 489582) {
             std::cout << "find: " << *it << std::endl;
        }
    }
}

void find_vec2() {
    int arr[6] = {1, 39, 923, 23902, 238904, 489582};
    std::vector<long> vec(arr, arr+6);

    for(std::vector<long>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::vector<long>::iterator it = std::find(vec.begin(), vec.end(), 489582);
    if(it != vec.end()) {
        std::cout << "find: " << *it << std::endl;
    }
}

int main() {
    del_vec();
    std::cout << std::endl;
    find_vec();
    std::cout << std::endl;
    find_vec2();
   
    return 0;
}


