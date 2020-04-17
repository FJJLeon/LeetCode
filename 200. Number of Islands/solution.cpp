#include<vector>
#include<stack>

using namespace std;

/**
 * 1. traverse all grid elem
 * 2. encounter unvisited land, BFS the island and mark all reachable land as visited
 * 
 * Runtime: 20 ms, O(N) N = m*n
 * Memory Usage: 9 MB, O(N)
*/
class Solution11 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int m, n;
        if ((m = grid.size()) == 0 || (n = grid[0].size()) == 0)
            return 0;
        vector<vector<bool>> visited = vector<vector<bool>>(m, vector<bool>(n, false));
        stack<pair<int, int>> flood;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (visited[i][j])
                    continue;
                visited[i][j] = true;
                
                if (grid[i][j] == '0')
                    continue;
                // flood the island, mark land as visited
                flood.push(make_pair(i, j));
                while (!flood.empty()) {
                    int x = flood.top().first, y = flood.top().second;
                    flood.pop();
                    if (x != 0 && !visited[x-1][y] && grid[x-1][y] == '1') {
                        visited[x-1][y] = true;
                        flood.push(make_pair(x-1, y));
                    }
                    if (x != m-1 && !visited[x+1][y] && grid[x+1][y] == '1') {
                        visited[x+1][y] = true;
                        flood.push(make_pair(x+1, y));
                    }
                    if (y != 0 && !visited[x][y-1] && grid[x][y-1] == '1') {
                        visited[x][y-1] = true;
                        flood.push(make_pair(x, y-1));
                    }
                    if (y != n-1 && !visited[x][y+1] && grid[x][y+1] == '1') {
                        visited[x][y+1] = true;
                        flood.push(make_pair(x, y+1));
                    }
                }
                ++count;
            }
        }
        return count;
    }
};

/**
 * Simplify above idea
 * a. don't mark land as visited, just modify input '1'
 * b. use loop of direction vector instend four if-statement
 * 
 * Runtime: 16 ms, faster than 46.73%, O(N)
 * Memory Usage: 8.5 MB, less than 100.00%, O(1) but input modified
*/
class Solution12 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int m, n;
        if ((m = grid.size()) == 0 || (n = grid[0].size()) == 0)
            return 0;
        stack<pair<int, int>> flood;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // not land, maybe '0' or '2'
                if (grid[i][j] != '1')
                    continue;                
                flood.push(make_pair(i, j));
                while (!flood.empty()) {
                    int x = flood.top().first, y = flood.top().second;
                    flood.pop();
                    for (auto& d : direct) {
                        int nx = x + d[0], ny = y + d[1];
                        if (valid(nx, ny, m, n) && grid[nx][ny] == '1') {
                            grid[nx][ny] = '2';
                            flood.push(make_pair(nx, ny));
                        }
                    }
                }
                // one island traversed
                ++count;
            }
        }
        return count;
    }
private:
    // direction vector
    const vector<vector<int>> direct = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    inline bool valid(int x, int y, int m, int n) {
        return x >= 0 && x < m && y >= 0 && y < n;
    }
};


/**
 * Recursive BFS
 * 
 * Runtime: 12 ms, faster than 90.99%
 * Memory Usage: 8.4 MB, less than 100.00%
*/
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] != '1')
                    continue;
                bfs(grid, i, j);
                ++count;
            }
        }
        
        return count;
    }
private:
    // direction vector
    const vector<vector<int>> direct = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    void bfs(vector<vector<char>>& grid, int x, int y) {
        if (x < 0 || x == grid.size() || y < 0 || y == grid[x].size() || grid[x][y] != '1') 
            return;
        // mark land
        grid[x][y] = '2';
        for (auto& d : direct) {
            bfs(grid, x+d[0], y+d[1]);
        }
    }
};
