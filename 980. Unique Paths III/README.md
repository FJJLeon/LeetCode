# 980. Unique Paths III

## 题目

题面：https://leetcode.com/problems/unique-paths-iii/

表面上是 [62. Unique Paths](https://leetcode.com/problems/unique-paths/) 和 [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) 的扩展。

起点用 1 标记而不是左上角，终点用 2 标记而不是右下角，仍旧存在用-1标记的障碍点，且可以朝4方向移动，计算从起点到终点的路径数量，但是要求**经过所有的非障碍点**。这样就完全不是原来的题了，这是在计算 **指定起点和终点的哈密顿路径的数量**，需要 DFS+回溯

## DFS+回溯 思路与实现

首先遍历一遍栅格，找到起点，并记录空白点的数量。

从起点开始 DFS，记录访问情况，按4方向搜索，搜索到终点时判断是否访问所有非障碍点，并进行回溯搜索。

其中，记录访问情况可以修改原栅格值，标记为 3 表示已访问过，当然修改输入参数不是一个好做法，因此可以使用一个辅助标记矩阵。本题标签中有一个位操作，提示可以使用位掩码来记录访问情况，本题的输入规模不会超过32位，若会超过可以用bitset。

``` c++
TC=O(3^(M*N)) 指数时间复杂度搜索，DFS可以朝三个方向继续搜索
SC=O(M*N) 最多需要的搜索栈深度为M*N，即整个栅格蛇形搜索

using pii = pair<int, int>;
enum {
    SQ_OBSTACLES = -1,
    SQ_EMPTY, // 0
    SQ_START, // 1
    SQ_END,   // 2
    SQ_VISITED// 3
};
class Solution {
public:
    int m, n, remain;
    // 是否访问过
    vector<vector<bool>> visited;
    // 搜索方向
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        visited.resize(m, vector<bool>(n, false));
        // 遍历栅格
        pii start;
        // 初始化为 1，即起点
        remain = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 记录非障碍点
                if (grid[i][j] == SQ_EMPTY) {
                    remain++;
                }
                // 找到起点
                else if (grid[i][j] == SQ_START) {
                    start = {i, j};
                }
            }
        }
        
        return dfs(start, grid);
    }
    
    int dfs(pii start, vector<vector<int>>& grid) {
        auto [x, y] = start;
        // 当前点为终点
        if (grid[x][y] == SQ_END) {
            // 判断是否已遍历完所有非障碍点
            // 值得注意的是这里不要写成
            // if (grid[x][y] = SQ_END && remain == 0) return 1
            // 当遇到终点时搜索就结束，不管是否遍历完所有非障碍点，以上实现会进入无效搜索
            return remain == 0;
        }
        // 标记已访问
        visited[x][y] = true;
        remain--;
        // 当前搜索情况下，从(x,y)点出发的哈密顿路径数量
        int count = 0;
        // 四方向搜索
        for (auto& dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            // 邻居点合法，未访问过，且非障碍
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny] || grid[nx][ny] == SQ_OBSTACLES)
                continue;
            count += dfs({nx, ny}, grid);
        }
        // 回溯
        visited[x][y] = false;
        remain++;
        
        return count;
    }
};
```

位掩码标记是否访问过，优化空间使用

``` c++
using pii = pair<int, int>;
enum {
    SQ_OBSTACLES = -1,
    SQ_EMPTY,
    SQ_START,
    SQ_END,
    SQ_VISITED
};
class Solution {
public:
    int m, n, remain;
    int visited;
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        // visited.resize(m, vector<bool>(n, false));
        visited = 0;
        
        pii start;
        remain = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == SQ_EMPTY) {
                    remain++;
                }
                else if (grid[i][j] == SQ_START) {
                    start = {i, j};
                }
            }
        }
        
        return dfs(start, grid);
    }
    
    int dfs(pii start, vector<vector<int>>& grid) {
        auto [x, y] = start;
        
        if (grid[x][y] == SQ_END) {
            return remain == 0;
        }
        
        // visited[x][y] = true;
        // 置位 (x*n+y)
        // 也可以用 visited ^= 1 << (x * n + y). a ^ 0 = a, a ^ 1 = ~a
        // 这样回溯的时候也相同异或操作即可
        visited |= 1 << (x * n + y);
        remain--;
        
        int count = 0;
        for (auto& dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            // 与运算判断访问情况
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || (visited & (1 << (nx * n + ny))) || grid[nx][ny] == SQ_OBSTACLES)
                continue;
            count += dfs({nx, ny}, grid);
        }
        
        // visited[x][y] = false;
        // 复位 (x*n+y)
        visited &= ~(1 << (x * n + y));
        remain++;
        
        return count;
    }
};
```

更进一步，用位掩码同时记录具体位置信息的访问情况，即兼有以上 visited 辅助标记数组和 remain 剩余未访问节点的作用

``` c++
using pii = pair<int, int>;
enum {
    SQ_OBSTACLES = -1,
    SQ_EMPTY,
    SQ_START,
    SQ_END
};
class Solution {
public:
    int m, n;
    int mask;
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        // visited.resize(m, vector<bool>(n, false));
        // 注意这个 mask 和 visited 是相反的
        // mask 第 x*n+y 位为 1 表示 (x,y) 是非障碍节点，且未访问过
        // 为 0 则可能是障碍，也可能是访问过的非障碍
        mask = 0;
        
        pii start;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 注意，非障碍点都需要记录，包括 start 和 end
                // 否则在判断是否前进搜索时要么需要额外判断是否是 start 和 end
                if (grid[i][j] != SQ_OBSTACLES) {
                    mask |= 1 << (i * n + j);
                }
                if (grid[i][j] == SQ_START) {
                    start = {i, j};
                }
            }
        }
        
        return dfs(start, grid);
    }
    
    int dfs(pii start, vector<vector<int>>& grid) {
        auto [x, y] = start;
        
        if (grid[x][y] == SQ_END) {
            // 注意 mask 消除 end 后全 0 则表示已访问所有非障碍点
            return (mask ^ (1 << x*n+y)) == 0;
        }
        
        // visited[x][y] = true;
        // 标记已访问过，实际上是 unset，等价 &= ~(1 << (x * n + y))
        mask ^= (1 << (x * n + y));
        
        int count = 0;
        for (auto& dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            // 判断未访问过，需要第 nx*n+ny 位为 0
            // 为 0 还可能是障碍，需要用 grid 进一步判断非障碍
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || !(mask & (1 << (nx * n + ny))) || grid[nx][ny] == SQ_OBSTACLES)
                continue;
            count += dfs({nx, ny}, grid);
        }
        
        // visited[x][y] = false;
        // 回溯标记未访问，实际上是 set，等价 |= 1 << (x * n + y)
        mask ^= (1 << (x * n + y));
        
        return count;
    }
};
```
