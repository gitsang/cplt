#include <iostream>
#include <memory>

struct A_struct {
    int num_;
    A_struct() : num_(0) {}
};typedef std::shared_ptr<A_struct> A;

struct B_struct {
    int num_;
    B_struct() : num_(0) {}
}typedef B;

int func(A a) {
    a->num_ = 2; 
}


int main() {
    A a(new struct A_struct);
    func(a);

    return 0;
}
