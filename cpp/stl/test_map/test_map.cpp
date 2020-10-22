#include <iostream>
#include <map>


int main(int argc, char* argv[]) {

    std::map<int, char> mp;
    mp[25] = 'a';
    mp[10] = 'b';
    mp[28] = 'c';
    mp[70] = 'd';
    mp[11] = 'e';
    mp[13] = 'f';
    mp[14] = 'f';
    mp[15] = 'f';
    //mp.erase(28);
    
    std::map<int, char>::iterator it;
    it = mp.find(29);
    if(it != mp.end()) {
        std::cout << (*it).first << ":" << (*it).second << std::endl;
    }else {
        std::cout << "not found!!" << std::endl;
    }

    /*
    for(it=mp.begin(); it!=mp.end(); it++) {
        std::cout << (*it).first << ":" << (*it).second << std::endl;
    }
    */


    return 0;
}
