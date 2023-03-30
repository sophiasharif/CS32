//
//  Set.cpp
//  project-2
//
//  Created by Sophia Sharif on 1/25/23.
//

#include "Set.h"
#include <iostream>

Set::Set()
    :m_head(nullptr), m_tail(nullptr) { }

Set::Set(const Set& other) {
    // set up
    m_head = nullptr;
    m_tail = nullptr;
    
    // copy nodes
    Node* p = other.m_head;
    while (p != nullptr) {
        insert(p->value);
        p = p->next;
    }
}

Set& Set::operator=(const Set& other) {
    
    // edge case: attempting to assign set to itself
    if (this == &other)
        return *this;
    
    // call copy constructor & destructor
    Set temp(other);
    swap(temp);
    return *this;
}

Set::~Set() {
    
    // edge case: set is empty
    if (m_head == nullptr)
        return;
    
    // delete all nodes
    while (m_head->next != nullptr) {
        m_head = m_head->next;
        delete m_head->previous;
    }
    delete m_head;
}

bool Set::empty() const {
    return m_head == nullptr;
}

int Set::size() const {
    int count = 0;
    Node* p = m_head;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

bool Set::insert(const ItemType& value) {
    
    // check if value is in set
    if (contains(value))
        return false;
    
    // edge case: list is empty
    if (m_head == nullptr) {
        m_head = new Node;
        m_head->value = value;
        m_head->next = nullptr;
        m_head->previous = nullptr;
        m_tail = m_head;
    }
    
    // edge case: value is less than first item
    else if (m_head->value > value){
        Node* newHead = new Node;
        newHead->value = value;
        newHead->next = m_head;
        newHead->previous = nullptr;
        m_head->previous = newHead;
        m_head = newHead;
    }

    // edge case: value is greater than the last item
    else if (m_tail->value < value) {
        Node* newTail = new Node;
        newTail->value = value;
        newTail->previous = m_tail;
        newTail->next = nullptr;
        m_tail->next = newTail;
        m_tail = newTail;
    }

    // value is guaranteed to belong between head and tail
    else {
        Node* p = m_head;
        while(p->next->value < value) // find insertion point
            p = p->next;
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = p->next;
        newNode->previous = p;
        p->next->previous = newNode;
        p->next = newNode;
    }

    return true;
}

bool Set::erase(const ItemType& value) {
    if (!contains(value))
        return false;
    
    // edge case: only one item in list
    if (m_head == m_tail) {
        Node* toDelete = m_head;
        m_head = nullptr;
        m_tail = nullptr;
        delete toDelete;
        return true;

    }
    
    // edge case: removing head
    else if (m_head->value == value) {
        Node* toDelete = m_head;
        m_head = m_head->next;
        m_head->previous = nullptr;
        delete toDelete;
        return true;

    }
    
    // edge case: removing tail
    else if (m_tail->value == value) {
        Node* toDelete = m_tail;
        m_tail = m_tail->previous;
        m_tail->next = nullptr;
        delete toDelete;
        return true;

    }

    // normal node removal:
    // value is guaranteed to exist and to be
    // between two nodes
    else {
        Node* toDelete = m_head;
        while (toDelete->value != value)
            toDelete = toDelete->next;
        toDelete->previous->next = toDelete->next;
        toDelete->next->previous = toDelete->previous;
        delete toDelete;
        return true;
    }
    
    return false;
}

bool Set::contains(const ItemType& value) const {
    // will not contain if list is empty
    if (m_head == nullptr)
        return false;
    
    // loop through and check if node exists
    Node* p = m_head;
    while (p != nullptr) {
        if (p->value == value)
            return true;
        p = p->next;
    }
    
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    // check input is valid
    if (pos < 0 || pos >= size())
        return false;
    
    Node* p = m_head;
    for (int i=0; i !=pos; i++) {
        p = p->next;
    }
    value = p->value;
    return true;
}

void Set::swap(Set& other) {
    // swap heads
    Node* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;
    
    // swap tails
    temp = m_tail;
    m_tail = other.m_tail;
    other.m_tail = temp;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // create a temporary storage set
    Set res;
    
    // loop through items in first set and insert
    for (int i=0; i!=s1.size(); i++) {
        ItemType temp;
        s1.get(i, temp);
        res.insert(temp);
    }
    
    // loop through items in second set and insert
    for (int i=0; i!=s2.size(); i++) {
        ItemType temp;
        s2.get(i, temp);
        res.insert(temp);
    }
    
    // copy res into result
    result = res;
}

void butNot(const Set& s1, const Set& s2, Set& result) {
    Set res;
    for (int i=0; i!= s1.size(); i++){
        ItemType temp;
        s1.get(i, temp);
        if (!s2.contains(temp))
            res.insert(temp);
    }
    result = res;
}
