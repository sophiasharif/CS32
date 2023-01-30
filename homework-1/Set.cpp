//
//  Set.cpp
//  homework-1
//
//  Created by Sophia Sharif on 1/19/23.
//

#include "Set.h"
#include <iostream>
using namespace std;

Set::Set() {
    setLength = 0;
}

bool Set::empty() const {
    return setLength == 0;
}

int Set::size() const {
    return setLength;
}

bool Set::insert(const ItemType& value) {
    // this function keeps the set ordered
    
    if (contains(value) || setLength == DEFAULT_MAX_ITEMS)
        return false;
    
    // edge cases
    if (setLength == 0)
        set[0] = value;
    else if (set[setLength-1] < value)
        set[setLength] = value;
    else if (set[0] > value) {
        shift(0);
        set[0] = value;
    }
    
    // loop until we find an item greater than value
    else
        for (int i = 0; i != setLength; i++)
            if (set[i] > value) {
                shift(i);
                set[i] = value;
                break;
            }
    setLength++;
    return true;
}


bool Set::erase(const ItemType& value) {
    for (int i=0; i != setLength; i++)
        if (set[i] == value) {
            setLength--;
            for (int j=i; j!=setLength; j++)
                set[j] = set[j+1];
            return true;
        }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i != setLength; i++)
        if (set[i] == value)
            return true;
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= size())
        return false;
    // implement this
    value = set[i];
    return true;
}

void Set::swap(Set& other) {
    for(int i=0; i < size() || i < other.size(); i++) {
        ItemType temp = set[i];
        set[i] = other.set[i];
        other.set[i] = temp;
    }
    int temp = setLength;
    setLength = other.setLength;
    other.setLength = temp;
}

void Set::dump() const {
    for (int i = 0; i != setLength; i++)
        cerr << set[i] << endl;
    cerr << "-----" << endl;
}

void Set::shift(int index) {
    if (index < 0 || index > size()-1 || size() == DEFAULT_MAX_ITEMS)
        cerr << "INVALID INDEX AT SET::SHIFT" << endl;
    for (int i=size(); i > index; i--) {
        set[i] = set[i-1];
    }
}
