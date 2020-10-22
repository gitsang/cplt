#include <iostream>
#include <map>

int main() {
    // define map object
    std::map<std::string, float> mp;
    //
    mp["jb"] = 98.5;
    mp["mc"] = 96.3;
    mp["js"] = 56.9;
    // 
    std::map<std::string, float>::iterator it;
    for(it=mp.begin(); it!=mp.end(); it++) {
        std::cout << (*it).first << ":"  << (*it).second << std::endl;
    }

    return 0; 
}
