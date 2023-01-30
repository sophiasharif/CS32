//
//  History.hpp
//  project1
//
//  Created by Sophia Sharif on 1/15/23.
//

#ifndef History_hpp
#define History_hpp

#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
  private:
    int m_rows;
    int m_cols;
    char m_displayGrid[MAXROWS][MAXCOLS];
};
#include <stdio.h>

#endif /* History_hpp */
