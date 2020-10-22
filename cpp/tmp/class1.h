#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

class class1 {
private:
    //static boost::shared_ptr<class1> self_;
    static class1* self_;
    class1() {

    }

public:
    ~class1() {
    
    }

    /*
    static boost::shared_ptr<class1> instance() {
        if(self_.get() == NULL) {
            self_.reset(new class1());
        }
        return self_;
    }
    */

    static class1* instance() {
        if(self_ == NULL) {
            self_ = new class1(); 
        } 
        return self_;
    }

    void print() {
        std::cout << "print" << std::endl;
    }
};

class1* class1::self_ = NULL;
