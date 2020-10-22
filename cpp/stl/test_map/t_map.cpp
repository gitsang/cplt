#include <iostream>
#include <map>

using namespace std;

int t_map() {
    map<int, string> mymap;
    mymap.insert(pair<int,string>(101, "aclive"));
    mymap.insert(map<int,string>::value_type(321, "hai"));
    // value_type is a pair type
    mymap[112] = "April";

    map<int, string>::iterator it = mymap.find(112);
    if(it != mymap.end()) {
        cout << "delete [112]: " << it->second << endl;
        mymap.erase(it);
    }
    cout << "map size = " << mymap.size() << endl;
    cout << "map max_size = " << mymap.max_size() << endl;
}

int main() {
    t_map();

    return 0;
}
