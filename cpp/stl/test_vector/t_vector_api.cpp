/*
 * test: vector::assign
 *
 * */

#include <iostream>
#include <vector>


void t_add() {
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector<int> vec3;

    /* assign 区间 左闭右开 */
    vec1.assign(7, 100);
    int intarr[] = {1, 7, 4, 5, 6};
    vec2.assign(intarr, intarr + 5);
    vec3.assign(vec2.begin()+1, vec2.end()-1);

    std::vector<int>::iterator it1 = vec1.begin();
    it1 = vec1.insert(it1, 11);/* only in this way, function can return iterator */
    vec1.insert(it1, 4, 12);
    it1 = vec1.begin();/* "it" will no longer valid, before insert */
    vec1.insert(it1 + 2, vec2.begin(), vec2.end());
    
    //display
    std::cout << "vec1: ";
    for(std::vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++) { // 迭代器
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "vec2: ";
    for(int i = 0; i < vec2.size(); i++) { // 下标
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "vec3: ";
    for(int i = 0; i < vec3.size(); i++) { // at
        std::cout << vec3.at(i) << " ";
    }
    std::cout << std::endl;
}
void t_size() {
    std::vector<int> vec4;

    vec4.push_back(10);
    while(vec4.back() != 0) {
        vec4.push_back(vec4.back()-1);
    }
    
    std::cout << "vec4: ";
    for(std::vector<int>::const_iterator it = vec4.cbegin(); it != vec4.cend(); it++) { // 迭代器
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\tvec4 size = " << vec4.size() << " capacity = " << vec4.capacity() << " max_size = " << vec4.max_size() << std::endl;
}
void t_clear() {
    std::vector<int> vec5;
    vec5.push_back(100);
    vec5.push_back(200);
    vec5.push_back(300);
    vec5.pop_back();
    vec5.push_back(400);
    vec5.push_back(500);
    vec5.push_back(600);
    
    std::cout << "vec5: ";
    for(std::vector<int>::iterator it = vec5.begin(); it != vec5.end(); it++) { // 迭代器
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    vec5.erase(vec5.begin()+1, vec5.begin()+3);// para same as assign
    std::cout << "\tafter erase [1, 3) vec5: ";
    for(std::vector<int>::iterator it = vec5.begin(); it != vec5.end(); it++) { // 迭代器
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "\t\tsize = " << vec5.size() << " capacity = " << vec5.capacity() << std::endl;

    vec5.clear();
    std::cout << "\tafter clear vec5: ";
    std::cout << "size = " << vec5.size() << " capacity = " << vec5.capacity() << std::endl;
    if(vec5.empty()) {
        std::cout << "\tvec5 is empty" << std::endl; 
    }
    
    std::vector<int>().swap(vec5);
    std::cout << "\tsize = " << vec5.size() << " capacity = " << vec5.capacity() << std::endl;
}
void t_data() {
    std::vector<int> vec6(3);
    int* p = vec6.data();

    *p = 60;
    *(p+1) = 61;
    p[2] = 62;

    /* An automatic reallocation happens if and only if the new vector size surpasses the current vector capacity. */
    vec6.emplace(vec6.begin()+1, 63);
    vec6.emplace(vec6.end(), 64);
    vec6.emplace_back(65);

    std::cout << "vec6(reverse): ";
    for(std::vector<int>::reverse_iterator it = vec6.rbegin(); it != vec6.rend(); it++) { // 逆向迭代器
        std::cout << *it << " ";
    }std::cout << std::endl;
    std::cout << "\tsize = " << vec6.size() << " capacity = " << vec6.capacity() << std::endl;

    std::cout << "\tfront = " << vec6.front() << " back = " << vec6.back() << std::endl;
}
void t_resize() {
    std::cout << "vec7: " << std::endl;

    std::vector<int> vec7 (100);
    std::cout << "\tsize = " << vec7.size() << " capacity = " << vec7.capacity() << std::endl;

    vec7.resize(50);
    std::cout << "\tsize = " << vec7.size() << " capacity = " << vec7.capacity() << std::endl;

    vec7.shrink_to_fit();
    std::cout << "\tsize = " << vec7.size() << " capacity = " << vec7.capacity() << std::endl;
}
void t_allocator() {
    std::vector<int> vec8;
    int* p;
    int i;

    // allocate an array with space for 5 elements
    p = vec8.get_allocator().allocate(5);

    // construct values in-place on the array:
    for(i=0; i<5; i++) {
        vec8.get_allocator().construct(&p[i], i);
    }

    std::cout << "vec8: ";
    for (i=0; i<5; i++) {
        std::cout << p[i] << ' ';
    }std::cout << '\n';

    // destroy and deallocate:
    for (i=0; i<5; i++) {
        vec8.get_allocator().destroy(&p[i]);
    }
    vec8.get_allocator().deallocate(p, 5);
}

int main() {
    t_add();
    t_size();
    t_clear();
    t_data();
    t_resize();
    t_allocator();

    return 0;
}
