#include <iostream>
#include <map>

int t_key_comp() {
    std::map<char,int> mymap;
    std::map<char,int>::key_compare mycomp = mymap.key_comp();

    mymap['a']=100;
    mymap['b']=200;
    mymap['c']=300;

    std::cout << "mymap contains:\n";

    char highest = mymap.rbegin()->first;     // key value of last element

    std::map<char,int>::iterator it = mymap.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    }while( mycomp((*it++).first, highest) );

    std::cout << '\n';

    return 0;
}

int t_value_comp() {
    std::map<char,int> mymap;

    mymap['x']=1001;
    mymap['y']=2002;
    mymap['z']=3003;

    std::cout << "mymap contains:\n";

    std::pair<char,int> highest = *mymap.rbegin();          // last element

    std::map<char,int>::iterator it = mymap.begin();
    do {
    std::cout << it->first << " => " << it->second << '\n';
    } while ( mymap.value_comp()(*it++, highest) );
    // value_compare value_comp() const;
    // return a function

    return 0;
}

int main() {
    t_key_comp();
    t_value_comp();
    return 0;
}
