
/* std::set
 *      #include <set>
 *      template<
 *          class Key, 
 *          class Compare = std::less<Key>, 
 *          class Allotor = std::allocator<Key>
 *      >class set;
 *
 *      std::set is an associative container that contains a sorted set of unique objects of type Key.
 *      Sorting is done using the key comparison function Compare.
 *      Search, removal, and insertion operations have "logarithmic complexity" -- O(log).
 *      Sets are usually implemented as red-black trees.
 *
 * member variable:
 *      key_type
 *      value_type
 *      size_type
 *      difference_type
 *      key_compare
 *      value_compare
 *
 *      allcator_type
 *      reference
 *      const_reference
 *      pointer
 *      const_pointer
 *
 *      iterator
 *      const_iterator
 *      reverse_iterator
 *      const_reverse_iterator
 *
 *      node_type
 *      insert_return_type
 *
 * member function:
 *      1. iterator: 
 *          begin(); end(); rbegin(); rend(); crbegin(); crend;
 *      2. capacity: 
 *          empty(); size(); max_size();
 *      3. change:   
 *          clear(); erase(); swap();
 *          insert(); emplace(); emplace_hint();
 *      4. find:
 *          count(); find();
 *          equal_range(); lower_bound(); upper_bound();
 *      5. observe:
 *          key_comp(); value_comp();
 *
 * non-member function:
 *      1. operator: 
 *          == / != / < / <= / > / >=
 *      2. std::swap(std::set)
 *      3. erase_if(std::set)
 * */

#include <iostream>
#include <set>

int t_set() {
    //test: init iterator
    int intarr[] = {75,23,65,42,13};
    std::set<int> st(intarr, intarr+5); // arr[0, 5)
    std::cout << "st contains:";
    for(std::set<int>::iterator it = st.begin(); it != st.end(); it++) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';

    //test: find erase clear swap
    std::set<int>::iterator it = st.find(75);
    st.erase(it);
    std::cout << "erase(75) size = " << st.size() << std::endl;
    st.clear(); // Removes all elements from the set container (which are destroyed), leaving the container with a size of 0.
    std::cout << "st.empty() : " << st.empty() << std::endl;
    std::set<int>().swap(st);
    std::cout << "size = " << st.size() << std::endl;
    std::cout << "max_size = " << st.max_size() << std::endl;
    
    //test: count insert
    st.insert(100);
    st.insert(101);
    st.insert(104);
    for(int i=100; i<105; i++) {
        std::cout << i;
        if(st.count(i)) {
        // return 1 if the container contains an element equivalent to val(value to search for), or zero otherwise
            std::cout << " is in st\n";
        }else {
            std::cout << " is not in st\n";
        }
    }

    return 0;
}

int t_bound() {
    //test: equal_range upper_bound lower_bound
    std::set<int> myset;
    std::set<int>::iterator it, itlow, itup;

    for(int i=1; i<=5; i++) {
        myset.insert(i*10);
    }

    std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
    ret = myset.equal_range(30);

    std::cout << "the lower bound points to: " << *ret.first << '\n';
    std::cout << "the lower_bound() points to: " << *myset.lower_bound(30) << '\n';
    std::cout << "the upper bound points to: " << *ret.second << '\n';
    std::cout << "the upper_bound() points to: " << *myset.upper_bound(30) << '\n';

    return 0;
}

int t_comp() {
    // in set: key == value, so key_comp == value_comp
    // key_comp and value_comp will only compare the position of element
    std::set<int> myset;

    for(int i = 0; i <= 5; i++) {
        myset.insert(i);
    }

    int highest = *myset.rbegin();
    std::set<int>::iterator it = myset.begin();
    while( myset.value_comp()(*it++, highest) ) {
       std::cout << ' ' << *it;
    }
    std::cout << '\n';

    it = myset.begin();
    while( myset.key_comp()(*it++, highest) ) {
       std::cout << ' ' << *it;
    }
    std::cout << '\n';

    return 0;
}

int main() {
    t_set();
    t_bound();
    t_comp();

    return 0;
}
