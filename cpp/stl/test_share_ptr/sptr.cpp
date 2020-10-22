#include <iostream>
#include <memory>

int main() {
    // original pointer used
    int i = 1, j = 2;
    int* ptr1 = &i;
    std::cout << *ptr1 << " " << ptr1 << " " << &ptr1 << std::endl;
    ptr1 = &j;
    std::cout << *ptr1 << " " << ptr1 << " " << &ptr1 << std::endl;
    ptr1 = NULL;

    // when use shared_ptr
    // each Object of shared_ptr point to "object" & "reference counter"
       
    // == new == //
    // new shared_ptr object binding with original pointer
    std::shared_ptr<int> p1(new int());
    // use_count() to see count of reference 
    std::cout << "p1.use_count = " << p1.use_count() << std::endl;

    // == assign == //
    //std::shared_ptr<int> p2 = new int(); //error
    // should use make_shared to assigned shared_ptr
    std::shared_ptr<int> p2 = std::make_shared<int>();
    std::cout << "p2.use_count = " << p2.use_count() << std::endl;
    
    // == reset == // 
    // relieve the connecting of shared_ptr
    p1.reset();
    std::cout << "p1.use_count = " << p1.use_count() << std::endl;
    // when use reset with parameter, counter will be changed to 1
    p2.reset(new int(34));
    std::cout << "p2.use_count = " << p2.use_count() << std::endl;
    // or you can use nullptr to reset it
    p2 = nullptr;
    std::cout << "p2.use_count = " << p2.use_count() << std::endl;


    // shared_ptr is a pseudo pointer
    // we can use * -> == to it
    std::shared_ptr<int> p3 = std::make_shared<int>();
    *p3 = 123;
    std::cout << "p3.use_count = " << p3.use_count() << std::endl;
    std::shared_ptr<int> p4(p3);
    std::cout << "p3.use_count = " << p3.use_count() << std::endl;
    std::cout << "p4.use_count = " << p4.use_count() << std::endl;
    if(p3 == p4) {
        std::cout << "p3 and p4 are pointing to the same pointer" << std::endl;
    }
    

    return 0; 
}
