
/*  test:
 *      equal_range(); upper_bound(); lower_bound();
 * */

/*  std::pair<iterator, iterator> map::equal_range(const Key& key);
 *
 *  reference:
 *      get the range of equal elements:
 *  
 *  return: 
 *      a pair of iterator
 *      - first is lower_bound() of range(point to the first element who is not less than key)
 *      - second is upper_bound() of range(point to the first element who is more than key)
 * */

#include <iostream>
#include <map>
//using namespace std;

int t_equal_range() {
    std::map<char, int> mymap;
    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    mymap['d'] = 40;

    std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';

    return 0;
}

int t_bound() {
    std::map<char, int> mymap;
    std::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow=mymap.lower_bound ('b');  // itlow points to b
    itup=mymap.upper_bound ('d');   // itup points to e (not d!)

    mymap.erase(itlow, itup);        // erases [itlow, itup)

    for (std::map<char, int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}


int main() {
    t_equal_range();
    t_bound();
    return 0;
}
