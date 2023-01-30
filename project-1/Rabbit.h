//
//  rabbit.hpp
//  project1
//
//  Created by Sophia Sharif on 1/13/23.
//

#ifndef rabbit_hpp
#define rabbit_hpp

#include <stdio.h>

class Arena;

class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* rabbit_hpp */
