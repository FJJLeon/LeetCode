# 695. Max Area of Island

## 题目

题面：https://leetcode-cn.com/problems/max-area-of-island/

四方向连接的是岛屿，找最大的岛屿面积

## 实现

经典 DFS，访问一个点，DFS访问它的四方向邻居，用一个标记矩阵或者直接在访问后修改原矩阵值来标记已经访问过。



``` C++
TC=O(RC)
SC=O(RC) \ O(1)

class Solution {
public:
    int m, n;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        int res = 0;
        // 对每个是 1 的点进行 DFS，更新最大岛屿面积
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1)
                    res = max(res, dfs(grid, i, j));
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j) {
        auto valid = [&](int i, int j) {
            return i >= 0 && i < m && j >= 0 && j < n;
        };
        // 合法点，且值为 1，才进行进一步 DFS
        if (!valid(i, j) || grid[i][j] != 1)
            return 0;
        // 修改值为 -1，表示已经访问过的岛屿点
        grid[i][j] = -1;
        // 四方向 DFS
        int res = 1 
                + dfs(grid, i + 1, j)
                + dfs(grid, i - 1, j)
                + dfs(grid, i, j + 1)
                + dfs(grid, i, j - 1);
        return res;
    }
};
```

基于栈的迭代DFS写法

``` c++
TC=O(RC)
SC=O(RC)

class Solution {
public:
    int m, n;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        vector<pair<int, int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};
        auto valid = [&](int i, int j) {
            return i >= 0 && i < m && j >= 0 && j < n;
        };
        
        m = grid.size(), n = grid[0].size();
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int area = 0;
                    // 用栈来记录邻居点
                    stack<pair<int, int>> st;
                    st.push({i,j});
                    while (!st.empty()) {
                        auto [r, c] = st.top(); st.pop();
                        // 合法点，且值为 1，才进行进一步 DFS
                        if (!valid(r, c) || grid[r][c] != 1)
                            continue;
                        area++;
                        // 修改值为 -1，表示已经访问过的岛屿点
                        grid[r][c] = -1;
                        // 四方向 DFS
                        for (int i = 0; i < 4; i++) {
                            auto [dr, dc] = dir[i];
                            auto nr = r + dr, nc = c + dc;
                            st.push({nr, nc});
                        }
                    }
                    // 更新最大岛屿面积
                    res = max(res, area);
                }
            }
        }
        return res;
    }
};
```
改成用 Queue 就是 BFS
