# 329. Longest Increasing Path in a Matrix

## 题目

题面：https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

**m x n** 矩阵，找到最长的严格递增路径，四邻域。

## 思路与实现

### 1. 记忆化DFS

粗一看想到的是转换为有向图，递增的邻居之间才有有向边，在图中DFS找最长路径。

但是DFS的起点在哪呢，一顿想发现要从每个点都进行一次DFS，但是需要把结果记录下来，类似动态规划的思想。若从其他起点开始的路径搜索到某个之前已经DFS过的点，就可以复用结果。是个单纯前向搜索，不需要回溯。

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int m, n;
    vector<vector<int>> cache;
    vector<vector<int>> dirs{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        // 保存从 (i,j) 开始的最长路径长度
        cache = vector<vector<int>>(m, vector<int>(n, -1));
        // 从每个点开始 DFS，维护最长结果
        int res = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res = max(res, dfs(i, j, matrix));
            }
        }
        return res;
    }
    
    int dfs(int i, int j, vector<vector<int>>& matrix) {
        // 已经访问过，直接返回
        if (cache[i][j] != -1)
            return cache[i][j];
        // 四方向搜索
        int tmp = 1, cell = matrix[i][j];
        for (auto& dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            // 邻居点合法，且递增才能继续DFS
            if (ni < 0 || ni >= m || nj < 0 || nj >= n || cell >= matrix[ni][nj])
                continue;
            tmp = max(tmp, dfs(ni, nj, matrix) + 1);
        }
        // 记录结果
        cache[i][j] = tmp;
        return tmp;
    }
};
```

### 2. 根据入度拓扑遍历

实际上，得到的图是一个有向无环图DAG，可以使用拓扑排序+层序遍历的方式得到最长路径

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> lens(m, vector<int>(n, -1)), in(m, vector<int>(n, 0));
        vector<vector<int>> dirs{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        // 计算
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cur = matrix[i][j];
                for (auto& dir : dirs) {
                    int x = i + dir[0], y = j + dir[1];
                    // ngh valid but ngh >= cur, skip
                    if (x < 0 || x >= m || y < 0 || y >= n || cur <= matrix[x][y])
                        continue;
                    // cur > ngh, ngb -> cur 存在一条有向边, cur 入度增加
                    in[i][j]++;
                }
            }
        }
        // 入度为 0 的点，首先入栈
        stack<pair<int, int>> st;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!in[i][j]) {
                    lens[i][j] = 1;
                    st.push({i, j});
                }
            }
        }
        // 四方向遍历，更新邻居的入度，为 0 时作为新的起点
        while (!st.empty()) {
            auto [x, y] = st.top(); st.pop();
            int cell = matrix[x][y];
            for (auto& dir : dirs) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || cell >= matrix[nx][ny])
                    continue;
                lens[nx][ny] = max(lens[nx][ny], lens[x][y] + 1);
                in[nx][ny]--;
                if (in[nx][ny] == 0)
                    st.push({nx, ny});
            }
        }
        // 计算结果
        int res = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res = max(res, lens[i][j]);
            }
        }
        return res;
    }
};
```
