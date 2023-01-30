//
//  main.cpp
//  project-2
//
//  Created by Sophia Sharif on 1/25/23.
//

#include <iostream>
#include <cassert>
#include "Set.h"
using namespace std;

int main() {
    
//    // ITEMTYPE = STRING TESTS
//    Set set = Set();
//    string test = "";
//
//    assert(set.size() == 0);
//    assert(!set.get(0, test));
//    assert(!set.erase("y"));
//    assert(!(set.contains("y")));
//    assert(set.insert("y"));
//    assert(set.size() == 1);
//    assert((set.contains("y")));
//    assert(set.get(0, test) && test=="y");
//    assert(!set.get(1, test));
//    assert(!set.get(-1, test));
//    assert(!set.insert("y"));
//    assert(set.erase("y"));
//    assert(set.size() == 0);
//    assert(set.insert("y"));
//    assert(set.insert("c"));
//    assert(set.erase("c"));
//    assert(set.size() == 1);
//    assert(set.insert("c"));
//    assert(set.erase("y"));
//    assert(set.size() == 1);
//    assert(set.insert("y"));
//    assert(!set.insert("c"));
//    assert(set.contains("c"));
//    assert(set.insert("z"));
//    assert(set.insert("d"));
//    assert(set.insert("a"));
//    assert(set.insert("f"));
//    assert(set.size() == 6);
//    assert(set.erase("c"));
//    assert(set.erase("f"));
//    assert(set.erase("d"));
//    assert(set.size() == 3);
//    assert(set.insert("d"));
//    assert(set.insert("f"));
//    assert(set.insert("c"));
//    assert(set.erase("z"));
//    assert(set.size()==5);
//    // linked list now is: a c d f y
//
//    // test get
//    assert(!set.get(-1, test));
//    assert(!set.get(5, test));
//    assert(set.get(0, test) && test=="a");
//    assert(set.get(1, test) && test=="c");
//    assert(set.get(2, test) && test=="d");
//    assert(set.get(3, test) && test=="f");
//    assert(set.get(4, test) && test=="y");
//
//    Set set2;
//    set2.insert("j");
//    set2.insert("k");
//    set2.insert("l");
//
//    // test swap
//    set2.swap(set);
//    assert(set2.size() == 5);
//    assert(set2.get(0, test) && test=="a");
//    assert(set2.get(4, test) && test=="y");
//    assert(set.size() == 3);
//    assert(set.get(0, test) && test=="j");
//    assert(set.get(2, test) && test=="l");
//
//    Set set3 = set;
//    assert(set.size() == set3.size());
//    assert(set3.get(0, test) && test=="j");
//    assert(set3.get(2, test) && test=="l");
//
//    // test assignment operator
//    set3 = set2;
//    assert(set3.size() == 5);
//    assert(set3.get(0, test) && test=="a");
//    assert(set3.get(4, test) && test=="y");
//
//    // test unite
//    unite(set, set2, set3);
//    assert(set3.size() == 8);
//    unite(set3, set, set2);
//    assert(set2.size() == 8);
//    Set set4;
//    unite(Set(), Set(), set4);
//    assert(set4.size() == 0);
//    unite(set4, set, set3);
//    assert(set.size() == set3.size());
//
//
//    // given tests
//    Set ss;  // ItemType is std::string
//    ss.insert("ccc");
//    ss.insert("aaa");
//    ss.insert("bbb");
//    ItemType x = "xxx";
//    assert(!ss.get(3, x)  &&  x == "xxx");
//    assert(ss.get(1, x)  &&  x == "bbb");
    
// ITEMTYPE = INT TESTS
    int arr1[5] = {2, 8, 3, 9, 5};
    int arr2[5] = {6, 3, 8, 5, 10};
    int uniteArr[7] = {9, 3, 6, 5, 10, 2, 8};
    int butNotArr[2] = {9, 2};
    
    Set s1, s2;
    for (int i=0; i!=5; i++){
        s1.insert(arr1[i]);
        s2.insert(arr2[i]);
    }
    
    // unite testing
    Set uniteS;
    unite(s1, s2, uniteS);
    assert(uniteS.size() == 7);
    for (int i=0; i<7; i++) {
        assert(uniteS.contains(uniteArr[i]));
    }
    // check we can pass unite() the same set:
    unite(uniteS, Set(), uniteS);
    for (int i=0; i<7; i++) {
        assert(uniteS.contains(uniteArr[i]));
    }
    
    // but not testing
    Set butNotSet;
    butNot(s1, s2, butNotSet);
    assert(butNotSet.size() == 2);
    for (int i=0; i<2; i++) {
        assert(butNotSet.contains(butNotArr[i]));
    }
    assert(!butNotSet.contains(3) && !butNotSet.contains(8));
    // check we can pass butNot the same set:
    butNot(s1, Set(), s1);
    for (int i=0; i!=5; i++){
        assert(s1.contains(arr1[i]));
    }
    // edge cases:
    Set t;
    butNot(Set(), Set(), t);
    assert(t.size() == 0);
    unite(Set(), Set(), t);
    assert(t.size() == 0);
    
    
    cout << "all test cases passed!" << endl;
}


