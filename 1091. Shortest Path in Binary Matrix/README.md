# 1091. Shortest Path in Binary Matrix

## 题目

题面：https://leetcode.com/problems/shortest-path-in-binary-matrix/

找一条全0路径从左上角到右下角

## 实现

### BFS

``` c++
TC=O(N^2)
SC=O(N^2)
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // 索引 (x, y) = x * n + y
        // visited 同时保存左上角点到该点的最短 clear path 长度
        vector<int> visited(n*n, -1);
        queue<int> q;
        // 只有当左上角为 0 才能开始
        if (grid[0][0] == 0) {
            q.push(0);
            visited[0] = 1;
        }
        // BFS
        while (!q.empty()) {
            int idx = q.front(); q.pop();
            int x = idx / n, y = idx % n;
            int len = visited[idx];
            // 8方向前进
            for (int sx = -1; sx <= 1; sx++) {
                for (int sy = -1; sy <= 1; sy++) {
                    int nx = x + sx, ny = y + sy;
                    // 跳过矩阵外和自身
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n || (nx == 0 && ny == 0))
                        continue;
                    // 没访问过 + 可通行
                    if (visited[nx*n + ny] == -1 && grid[nx][ny] == 0) {
                        // 更新 clear path 长度并入队
                        visited[nx*n + ny] = len + 1;
                        q.push(nx*n + ny);
                    }
                }
            }
        }
        return visited[n*n-1];
    }
};
```
