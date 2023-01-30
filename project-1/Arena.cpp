//
//  arena.cpp
//  project1
//
//  Created by Sophia Sharif on 1/13/23.
//

#include <stdio.h>
#include <iostream>
using namespace std;

#include "globals.h"
#include "Arena.h"
#include "Rabbit.h"
#include "Player.h"

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////


Arena::Arena(int nRows, int nCols)
  :m_history(nRows, nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    for (int k = 0; k < m_nRabbits; k++)
        delete m_rabbits[k];
    delete m_player;
}

History& Arena::history() {
    return m_history;
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
    return m_nRabbits;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nRabbits; k++)
    {
        Rabbit* rp = m_rabbits[k];
        if (rp->row() == r  &&  rp->col() == c)
            count++;
    }
    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

        // Indicate each rabbit's position
    for (int k = 0; k < m_nRabbits; k++)
    {
        const Rabbit* rp = m_rabbits[k];
        char& gridChar = displayGrid[rp->row()-1][rp->col()-1];
        switch (gridChar)
        {
          case '.':  gridChar = 'R'; break;
          case 'R':  gridChar = '2'; break;
          case '9':  break;
          default:   gridChar++; break;  // '2' through '8'
        }
    }

      // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a rabbit on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

    if (m_nRabbits == MAXRABBITS)
        return false;
    m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
    m_nRabbits++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
      // Move all rabbits
    for (int k = m_nRabbits-1; k >= 0; k--)
    {
        Rabbit* rp = m_rabbits[k];
        rp->move();

        if (m_player != nullptr  &&
                rp->row() == m_player->row()  &&  rp->col() == m_player->col())
            m_player->setDead();

        if (rp->isDead())
        {
            delete rp;

              // The order of Rabbit pointers in the m_rabbits array is
              // irrelevant, so it's easiest to move the last pointer to
              // replace the one pointing to the now-deleted rabbit.  Since
              // we are traversing the array from last to first, we know this
              // last pointer does not point to a dead rabbit.

            m_rabbits[k] = m_rabbits[m_nRabbits-1];
            m_nRabbits--;
        }
    }

      // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}


// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // How dangerous is it to stand?
  int standDanger = computeDanger(a, r, c);

    // if it's not safe, see if moving is safer
  if (standDanger > 0)
  {
      int bestMoveDanger = standDanger;
      int bestMoveDir = NORTH;  // arbitrary initialization

        // check the four directions to see if any move is
        // better than standing, and if so, record the best
      for (int dir = 0; dir < NUMDIRS; dir++)
      {
          int rnew = r;
          int cnew = c;
          if (attemptMove(a, dir, rnew, cnew))
          {
              int danger = computeDanger(a, rnew, cnew);
              if (danger < bestMoveDanger)
              {
                  bestMoveDanger = danger;
                  bestMoveDir = dir;
              }
          }
      }

        // if moving is better than standing, recommend move
      if (bestMoveDanger < standDanger)
      {
          bestDir = bestMoveDir;
          return true;
      }
  }
  return false;  // recommend standing
}

int computeDanger(const Arena& a, int r, int c)
{
    // Our measure of danger will be the number of rabbits that might move
    // to position (r,c).  If a rabbit is at that position, it is fatal,
    // so a large value is returned.

  if (a.numberOfRabbitsAt(r,c) > 0)
      return MAXRABBITS+1;

  int danger = 0;
  if (r > 1)
      danger += a.numberOfRabbitsAt(r-1,c);
  if (r < a.rows())
      danger += a.numberOfRabbitsAt(r+1,c);
  if (c > 1)
      danger += a.numberOfRabbitsAt(r,c-1);
  if (c < a.cols())
      danger += a.numberOfRabbitsAt(r,c+1);

  return danger;
}
