//
//  main.cpp
//  homework-1
//
//  Created by Sophia Sharif on 1/19/23.
//

#include <iostream>
#include "CardSet.h"
using namespace std;

int main() {
    CardSet test;
    test.add(1);
    test.add(2);
    test.add(34);
    test.add(34);
    test.add(34);
    test.add(34);
    test.add(3);
    test.add(134);
    cout << test.size() << endl;
    cout << "---" << endl;
    test.print();
}
