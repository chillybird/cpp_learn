// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y)
{
    queue<pair<int, int>> que;
    que.push({x, y});
    visited[x][y] = true;

    while(!que.empty())
    {
        pair<int, int> curr = que.front();
        que.pop();
        int curr_x = curr.first;
        int curr_y = curr.second;
        for(int i = 0; i < 4; i++)
        {
            int next_x = curr_x + dir[i][0];
            int next_y = curr_y + dir[i][1];
            if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
                continue;
            if (!visited[next_x][next_y] && grid[next_x][next_y] == '1')
            {
                que.push({next_x, next_y});
                visited[next_x][next_y] = true;
            }
        }
    }
}

int numIsland(vector<vector<char>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

    int result = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(!visited[i][j] && grid[i][j] == '1')
            {
                visited[i][j] = true;
                result++;
                bfs(grid, visited, i, j);
            }
        }
    }

    return result;
}

int main()
{
    vector<vector<char>> grid {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','1'},
        {'0','0','1','1','0'}
    };

    cout << numIsland(grid) << endl;

    return 0;
}