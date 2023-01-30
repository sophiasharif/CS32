//
//  main.cpp
//  hw-1-p5
//
//  Created by Sophia Sharif on 1/21/23.
//

#include <iostream>
#include "newSet.h"
#include <cassert>
using namespace std;

int main() {
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    b.insert("a"); b.insert("b"); b.insert("c"); b.insert("d"); b.insert("e");
    Set c = b;
    assert(!b.insert("f"));
    assert(!c.insert("f"));
    assert(c.size() == b.size());
    b.erase("e"); b.erase("a");
    assert(b.size() == 3);
    assert(c.size() == 5);
    a.insert("f"); a.insert("g");
    assert(!a.empty());
    a=b;
    assert(a.size() == b.size());
    b.erase("b");
    string temp;
    a.get(0, temp);
    assert(temp == "b");
}

