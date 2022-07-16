# 576. Out of Boundary Paths

## 题目

题面：https://leetcode-cn.com/problems/out-of-boundary-paths/

从 [startRow, startColumn] 开始，每步可以四方向移动，经过最多 maxMove 步，走出边界，问有多少这样的路径走法，路径可以经过重复的点。

## 思路与实现

用一个矩阵表示经过某步后从起始点能走到该点的路径数量，每步对矩阵进行**扩散**的操作。初始时只置 [startRow, startColumn] 点为 1，每步对每个点进行遍历，从上下左右四个点可以走到当前点，这些点前一步的路径数量之和，即为当前步从起始点走到该点的路径数量。若下一步发现路径出界了，则更新出界路径数量。

该思路可以通过记忆化搜索或动态规划来实现。

### 1. 记忆化搜索

除了矩阵的两个维度，memo 还需要一个维度记录当前步数。

``` c++
TC=O(m*n*maxMove)
SC=O(m*n*maxMove)

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
class Solution {
public:
    const int mod = 1e9 + 7;
    vvvi memo;
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        // memo[k][i][j] 表示第 k 步从起始点走到 (i,j) 的路径数量
        memo = vvvi(maxMove + 1, vvi(m, vi(n, -1)));
        return dfs(startRow, startColumn, maxMove, m, n, memo);
    }
    
    int dfs(int i, int j, int move, int m, int n, vvvi& memo) {
        // 当前步出界，直接返回一条合法路径
        if (i < 0 || i == m || j < 0 || j == n)
            return 1;
        // 步数耗尽，余下 DFS 已无合法路径
        if (move == 0)
            return 0;
        // 若从当前点 (i,j) 笔直走 move 步也出不了界，直接返回无合法路径，剪枝
        if (i - move >= 0 && i + move < m && j - move >= 0 && j + move < n) {
            return 0;
        }
        // 已搜索过，直接返回记录的路径数量
        if (memo[move][i][j] >= 0)
            return memo[move][i][j];
        // 四方向 DFS，需要 mod
        memo[move][i][j] = ((dfs(i + 1, j, move - 1, m, n, memo)
                         + dfs(i - 1, j, move - 1, m, n, memo)) % mod
                         + (dfs(i, j + 1, move - 1, m, n, memo)
                         + dfs(i, j - 1, move - 1, m, n, memo)) % mod) 
                         % mod;
        return memo[move][i][j];
    }
};
```

### 2. 动态规划

自底向上动态规划，从走 1 步迭代到走 maxMove 步。注意到每次转移更新时，只需要前一步的动规矩阵，因此可以进行空间优化，只用两个 m*n 的矩阵。

``` c++
TC=O(m*n*maxMove)
SC=O(m*n)

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
class Solution {
public:
    int mod = 1e9+7;
    void addMod(int& origin, int added) {
        origin = (origin + added) % mod;
    }
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        vvi dp(m, vi(n)), dup(m, vi(n));
        // 初始化第一步，只有 [startRow, startColumn] 点为 1
        dp[startRow][startColumn] = 1;
        int res = 0;
        // 走 maxMove 步，每次转移更新
        for (int s = 0; s < maxMove; s++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    // 若能四方形出界，更新路径数量
                    if (i == 0) addMod(res, dp[i][j]);
                    if (i == m - 1) addMod(res, dp[i][j]);
                    if (j == 0) addMod(res, dp[i][j]);
                    if (j == n - 1) addMod(res, dp[i][j]);
                    // 在 dup 数组中用 dp 的前一步四方向来源更新 当前步路径数量
                    int tmp = 0;
                    if (i > 0) addMod(tmp, dp[i-1][j]);
                    if (i < m - 1) addMod(tmp, dp[i+1][j]);
                    if (j > 0) addMod(tmp, dp[i][j-1]);
                    if (j < n - 1) addMod(tmp, dp[i][j+1]);
                    dup[i][j] = tmp;
                }
            }
            // dp 更新为 dup
            dp.swap(dup);
        }
        
        return res;
    }
};
```
简化实现
``` c++
TC=O(m*n*maxMove)
SC=O(m*n)

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
class Solution {
public:
    int mod = 1e9+7;
    void addMod(int& origin, int added) {
        origin = (origin + added) % mod;
    }
    const vector<pair<int, int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        vvi dp(m, vi(n)), dup(m, vi(n));
        dp[startRow][startColumn] = 1;
        int res = 0;
        for (int s = 0; s < maxMove; s++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int tmp = 0;
                    // 四方形 DFS
                    for (auto [di, dj] : dir) {
                        int ni = i + di, nj = j + dj;
                        // 出界，更新 res
                        if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                            addMod(res, dp[i][j]);
                        // 不出界，更新 dup[i][j]
                        else
                            addMod(tmp, dp[ni][nj]);
                    }
                    dup[i][j] = tmp;
                }
            }
            dp.swap(dup);
        }
        
        return res;
    }
};
```
