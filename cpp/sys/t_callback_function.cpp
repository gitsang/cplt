#include <iostream>

int add(int a, int b) {
    return a + b;
} 

int dec(int a, int b) {
    return a - b;
}

int libfun(int c, int d, int (* pDis)(int a, int b)) {
    std::cout <<  pDis(c, d) << std::endl;
}

int main() {
    libfun(5, 6, add);
    libfun(8, 2, dec);

    return 0;
}
