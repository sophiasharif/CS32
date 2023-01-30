//
//  History.cpp
//  project1
//
//  Created by Sophia Sharif on 1/15/23.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
  :m_rows(nRows), m_cols(nCols)
{
    int r, c;
    for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++)
            m_displayGrid[r-1][c-1] = '.';
}

bool History::record(int r, int c)
{
    if (r <= 0 || r > m_rows || c > m_cols || c <= 0)
        return false;
    if (m_displayGrid[r-1][c-1] == '.')
        m_displayGrid[r-1][c-1] = 'A';
    else if (m_displayGrid[r-1][c-1] != 'Z')
        m_displayGrid[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    int r, c;
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << m_displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
}
