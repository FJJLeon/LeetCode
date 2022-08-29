# [827. Making A Large Island](https://leetcode.com/problems/making-a-large-island/)

## 题目

矩阵 1 表示陆地、0 表示海洋，有若干岛屿，问把最多一个 0 变成 1 能形成的最大岛屿大小。

## 实现

经典岛屿问题，BFS 或者 并查集遍历路地点记录独立岛屿（大小和岛屿编号）(类似 [200](../200.%20Number%20of%20Islands/README.md))，再遍历所有海洋点判断四方形独立岛屿大小的和。

### 1. 并查集

``` c++
TC=O(MN)
SC=O(MN)
class Solution {
public:
    int m, n;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int largestIsland(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        UF uf(m * n);
        
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == 1) {
                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= m ||ny < 0 || ny >= n || grid[nx][ny] != 1)
                            continue;
                        uf.merge(x * n + y, nx * n + ny);
                    }
                }
            }
        }
        
        set<int> ccs;
        int res = -1;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                // 对每个海洋点
                if (grid[x][y] == 0) {
                    ccs.clear();
                    // 记录四方形独立岛屿
                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= m ||ny < 0 || ny >= n || grid[nx][ny] != 1)
                            continue;
                        // 记录对应的代表（即岛屿编号）
                        ccs.insert(uf.find(nx * n + ny));
                    }
                    // 计算 1 + 独立岛屿大小的和
                    int cur = 1;
                    for (int cc : ccs)
                        cur += uf.getRank(cc);
                    // 更新最大岛屿大小
                    res = max(res, cur);
                }
            }
        }
        return res == -1 ? n * n : res;
    }
private:
    class UF {
        int n;
        // 代表、岛屿大小
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
            return rep[x] == x ? x : rep[x] = find(rep[x]);
        }
        
        bool merge(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py)
                return false;
            
            // rank[px] += rank[py];
            // rep[py] = px;
            // return true;
            
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
        
        int getRank(int x) const {
            return rank[x];
        }
    };
};
```

### 2. BFS

不同于并查集使用内部的 代表数组表示了（连通分量编号） 和 秩数组（连通分量大小），BFS需要修改岛屿值（大于2）或者用一个映射矩阵来记录编号，需要额外一个映射记录编号和对应岛屿大小
``` c++
TC=O(MN)
SC=O(MN)
class Solution {
public:
    int m, n;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int largestIsland(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        // 岛屿编号和 -> 对应岛屿大小
        unordered_map<int, int> cc2size;
        int cc = 2;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == 1) {
                    int cnt = 0;
                    dfs(grid, x, y, cc, cnt);
                    cc2size[cc] = cnt;
                    cc++;
                }
            }
        }
        
        set<int> ccs;
        int res = -1;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == 0) {
                    ccs.clear();
                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= m ||ny < 0 || ny >= n || grid[nx][ny] == 0)
                            continue;
                        // 记录岛屿编号
                        ccs.insert(grid[nx][ny]);
                    }
                    // 计算 1 + 独立岛屿大小的和，并更新
                    int cur = 1;
                    for (int cc : ccs)
                        cur += cc2size[cc];
                    res = max(res, cur);
                }
            }
        }
        return res == -1 ? n * n : res;
    }

    void dfs(vector<vector<int>>& grid, int x, int y, int cc, int& cnt) {
        // 修改岛屿值为 编号 cc
        grid[x][y] = cc;
        cnt++;
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] != 1)
                continue;
            dfs(grid, nx, ny, cc, cnt);
        }
    }
};
```
