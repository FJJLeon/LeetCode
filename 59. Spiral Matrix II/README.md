# 59. Spiral Matrix II

## 描述

题面：https://leetcode.com/problems/spiral-matrix-ii/

用螺旋线填满一个 N*N 的矩阵，螺旋模拟

## 思路与实现

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