#include <iostream>
#include <string>

int main() {
    std::string ch1 = "aaa";
    std::string ch2;

    ch1 += "%s";
    ch2 = "bbb";

    std::cout << ch1 << std::endl;
    std::cout << ch2 << std::endl;

    return 0;
}
