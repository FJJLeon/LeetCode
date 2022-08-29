# 200. Number of Islands

Given a 2d grid map of `'1'`s (land) and `'0'`s (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:
```
Input:
11110
11010
11000
00000

Output: 1

Input:
11000
11000
00100
00011

Output: 3
```

## 实现

### 1. DFS

对每个 1 进行 DFS 遍历所有岛屿点，进行计数。DFS 遍历过程中修改同一个岛屿点的值。

``` c++
TC=O(MN)
SC=O(1) / O(MN)
class Solution {
public:
    int m, n;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        int cc = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    cc++;
                }
            }
        }
        return cc; 
    }
    
    void dfs(vector<vector<char>>& grid, int x, int y) {
        grid[x][y] = '2';
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] != '1')
                continue;
            dfs(grid, nx, ny);
        }
    }
};
```

### 2. 并查集

仍旧去看了并查集实现模板，还是不会直接写并查集。

一般并查集使用的索引是一维的，这里可以用二维索引转一维，也可以使用二维的 rep 数组。

``` c++
TC=O(MN α(MN))
SC=O(MN)

class Solution {
private:
    class UF {
        int n;
        vector<int> rep, rank;
    public:
        UF(int _n) : n(_n) {
            rep.resize(n);
            rank.resize(n, 1);
            for (int i = 0; i < n; i++) {
                rep[i] = i;
            }
        }
        
        int find(int x) {
            // 路径压缩
            return rep[x] == x ? x : rep[x] = find(rep[x]);
        }
        
        bool merge(int x, int y) {
            int px = find(x), py = find(y);
            // 已经是同一个，不需要进行合并
            if (px == py)
                return false;
            
            // 简单合并
            // rank[py] += rank[px];
            // rep[px] = py;

            // 按秩（此处为所代表岛屿数量）合并，小合到大
            if (rank[px] < rank[py]) {
                rank[py] += rank[px];
                rep[px] = py;
            }
            else {
                rank[px] += rank[py];
                rep[py] = px;
            }
            return true;
        }
    };
public:
    int m, n;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        
        UF uf(m * n);
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == '1') {
                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= m ||ny < 0 || ny >= n || grid[nx][ny] != '1')
                            continue;
                        // 单纯 merge，没有利用到返回值
                        uf.merge(x * n + y, nx * n + ny);
                    }
                }
            }
        }
        // merge 完成后再遍历所有岛屿点，用set计数独立岛屿数量
        set<int> s;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == '1') {
                    s.insert(uf.find(x * n + y));
                }
            }
        }
        return s.size();
    }

    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        
        UF uf = UF(m * n);
        int cc = 0;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == '1') {
                    // 发现新岛屿点，cc 自增
                    cc++;
                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= m ||ny < 0 || ny >= n || grid[nx][ny] != '1')
                            continue;
                        // 利用 merge 的返回值，若进行了合并（返回 true），cc 自减即 独立岛屿数量减 1
                        if (uf.merge(x * n + y, nx * n + ny))
                            cc--;
                    }
                }
            }
        }
        return cc;
    }
};
```
