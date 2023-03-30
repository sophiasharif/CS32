#include <iostream>
#include <queue>
using namespace std;

const char PATH = '.';
const char VISITED = '_';

class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    queue<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = VISITED;
    while (!coordStack.empty()) {
        
        Coord curr = coordStack.front();
        coordStack.pop();
        
        if (curr.r() == er && curr.c() == ec)
            return true;
        
        int dirs[4][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}};
        for (int i=0; i<4; i++) {
            int row = curr.r() + dirs[i][0];
            int col = curr.c() + dirs[i][1];
            if (row >=0 && row < nRows && col >=0 && col < nCols
                && maze[row][col] == PATH)
            {
                coordStack.push(Coord(row, col));
                maze[row][col] = VISITED;
                
            }
        }
        
    }
    return false;
}

int main()
{
string maze[10] = {
    "XXXXXXXXXX",
    "X..X...X.X",
    "X.XXXX.X.X",
    "X.X.X..X.X",
    "X...X.XX.X",
    "XXX......X",
    "X.X.XXXX.X",
    "X.XXX....X",
    "X...X..X.X",
    "XXXXXXXXXX"
};

if (pathExists(maze, 10,10, 5,3, 8,8))
    cout << "Solvable!" << endl;
else
    cout << "Out of luck!" << endl;
}
