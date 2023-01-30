#include <iostream>
#include "Set.h"
#include <cassert>
using namespace std;

int main() {
    Set s;
    assert(s.empty());
    s.insert("a");
    s.insert("b");
    s.insert("c");
    s.insert("d");
    s.insert("e");
    s.insert("f");
    assert(s.size() == 6);
    s.erase("d");
    string temp;
    s.get(4, temp);
    assert(temp == "f");
    assert(!s.contains("d"));
    Set t;
    t.swap(s);
    t.get(3, temp);
    assert(temp == "e");
    assert(!t.contains("d"));
    assert(t.size() == 5);
    assert(s.size() == 0);
}
