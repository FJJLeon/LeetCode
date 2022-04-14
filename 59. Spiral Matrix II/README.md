# 59. Spiral Matrix II

## 描述

题面：https://leetcode.com/problems/spiral-matrix-ii/

用螺旋线填满一个 N*N 的矩阵，螺旋模拟

## 思路与实现

### 1. 按圈四段循环遍历

按圈由外向内填满螺旋矩阵，每个圈分四段循环，每段长度quarter相等。

``` c++
TC = O(N^2)
SC = O(1)

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int cnt = 1, quarter;
        // 圈索引 c: 0 - (n+1)/2
        for (int c = 0; c < (n + 1) / 2; c++) {
            quarter = n - 2 * c - 1;
            // 填满一圈
            fillCycle(res, c, quarter, cnt);
        }
        return res;
    }
    
    inline void fillCycle(vector<vector<int>>& matrix, int c, int quarter, int& cnt) {
        // 对于奇数 n 的最内圈，只有一个数，quarter 为 0
        if (quarter == 0) {
            matrix[c][c] = cnt++;
            return;
        }
        // 使用四个循环遍历
        // 左上 -> 右上 [c][c] -> [c][c+quarter-1]
        for (int j = c; j < c + quarter; j++)
            matrix[c][j] = cnt++;
        // 右上 -> 右下 [c][c+quarter] -> [c+quarter-1][c+quarter]
        for (int i = c; i < c + quarter; i++)
            matrix[i][c + quarter] = cnt++;
        // 右下 -> 左下 [c+quarter][c+quarter] -> [c+quarter][c+1]
        for (int j = c + quarter; j > c; j--)
            matrix[c + quarter][j] = cnt++;
        // 左下 -> 左上 [c+quarter][c] -> [c+1][c]
        for (int i = c + quarter; i > c; i--)
            matrix[i][c] = cnt++;
    }
};
```

### 2.1. 方向数组替代

以上遍历过程中，四个行进方向使用方向数组表示。

在行进方向上，如果遇到非零值，则需要右转。

``` c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int cnt = 1;
        // 方向数组 [dr, dc]
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        // 方向数组索引
        int d = 0;
        // 当前矩阵位置
        int r = 0, c = 0;
        while (cnt <= n * n) {
            res[r][c] = cnt++;
            // [(r+dr)%n][(c+dc)%n] 若非零，则右转即使用下一个方向数组
            // C++这边负数取余问题需要 + N
            // 值得注意的是，最外圈行进时一个方向到末尾会回到开头从而触发转向
            if (res[(r + dir[d][0] + n) % n][(c + dir[d][1] + n) % n] != 0)
                d = (d + 1) % 4;
            // 行进一步
            r += dir[d][0];
            c += dir[d][1];
        }
        
        return res;
    }
};
```
### 2.2. 方向直接右转变换

以上方向数组 **[dr, dc]** 的变化实际上等价于 **dr, dc = dc, -dr**

``` c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int cnt = 1;
        int r = 0, c = 0;
        // 方向变换 [dr, dc]
        int dr = 0, dc = 1;
        while (cnt <= n * n) {
            res[r][c] = cnt++;
            // 右转 
            if (res[(r + dr + n) % n][(c + dc + n) % n] != 0) {
                // dr, dc = dc, -dr
                int t = dr;
                dr = dc;
                dc = -t;
            }
            
            r += dr;
            c += dc;
        }
        
        return res;
    }
};
```