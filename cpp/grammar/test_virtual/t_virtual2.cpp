#include <iostream>

class Base {
public: 
    Base() {
    }

public:
    void print() {
        std::cout << "Base" << std::endl;
    }

    virtual void vprint() {
        std::cout << "vBase" << std::endl;
    }
};
 
class Derived : public Base {
public:
    Derived() {
    }

public:
    void print(){
        std::cout << "Derived" << std::endl;
    }
    
    void vprint() {
        std::cout << "vDerived" << std::endl;
    }
};
 
int main() {
   Base *p1 = new Base();
   p1->print();
   p1->vprint();
   
   Derived *p2 = new Derived();
   p2->print();
   p2->vprint();
   
   Base *p3 = new Derived();
   p3->print();
   p3->vprint();
   
   return 0;
} 
