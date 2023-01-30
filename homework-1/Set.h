//
//  Set.hpp
//  homework-1
//
//  Created by Sophia Sharif on 1/19/23.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>
#include <string>

using ItemType = std::string;
const int DEFAULT_MAX_ITEMS = 160;

class Set
{
  public:
    Set();         // Create an empty set (i.e., one whose size() is 0).

    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if value is not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
     
    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
    
    void dump() const;
    
  private:
    int setLength;
    ItemType set[DEFAULT_MAX_ITEMS];
    void shift(int index);
        // shift over all elems starting from index by one spot;
        // "free up" index for insertion of another element.
        // does not check if index is valid
};


#endif /* Set_hpp */
