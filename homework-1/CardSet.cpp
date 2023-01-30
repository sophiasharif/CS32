//
//  CardSet.cpp
//  homework-1
//
//  Created by Sophia Sharif on 1/21/23.
//

#include "CardSet.h"
#include <iostream>
using namespace std;

CardSet::CardSet(): cardSet() {}

bool CardSet::add(unsigned long cardNumber) {
    return cardSet.insert(cardNumber);
}

int CardSet::size() const {
    return cardSet.size();
}

void CardSet::print() const {
    unsigned long value;
    for (int i=0; i!=cardSet.size(); i++) {
        cardSet.get(i, value);
        cout << value << endl;
    }
}
