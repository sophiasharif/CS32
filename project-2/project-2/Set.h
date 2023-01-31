//
//  Set.h
//  project-2
//
//  Created by Sophia Sharif on 1/25/23.
//

#ifndef Set_h
#define Set_h
#include <string>

using ItemType = std::string;

class Set
{
  public:
    
    Set();
    Set(const Set& other);
    Set& operator= (const Set& other);
    ~Set();
    
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
  private:
    struct Node
    {
        Node* next;
        Node* previous;
        ItemType value;
    };
    Node* m_head;
    Node* m_tail;
};

void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */

