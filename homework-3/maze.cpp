const char PATH = '.';
const char VISITED = '_';

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec) return true;
    maze[sr][sc] = VISITED;
    int dirs[4][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}};
    for (int i=0; i<4; i++)
        if (maze[sr + dirs[i][0]][sc + dirs[i][1]] == PATH && pathExists(maze, nRows, nCols, sr + dirs[i][0], sc + dirs[i][1], er, ec)) return true;
    return false;
}
