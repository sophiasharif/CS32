//
//  game.hpp
//  project1
//
//  Created by Sophia Sharif on 1/13/23.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <string>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* game_hpp */
