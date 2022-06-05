# 52. N-Queens II

## 题目

题面：https://leetcode.com/problems/n-queens-ii/

N 皇后，不同于 [51. N-Queens](https://leetcode.com/problems/n-queens/)，仅需返回合法放置的数量

## 实现

### 1. 简单回溯

类似 [51 题解](../51.%20N-Queens/README.md)，直接使用棋盘，在枚举时检查棋盘的三个方向来选择安全位置。

### 2. 空间优化

在给每一列选择一个位置时，需要判断前面已经放置的皇后是否会攻击到，这样的攻击来自三个方向：

* 横向，即每一行，共 N 条，故索引即为 row
* 对角线，即左上到右下的对角线，共 2N-1 条，对于这样的某一条对角线上位置，其 row 和 col 的差值相等，$row - col  \in \{-N+1, N-1\}$，故索引设为 row - col + N - 1
* 反对角线，即左下到右上的对角线，共 2N-1 条，对于这样的某一条对角线上位置，其 row 和 col 的和相等，$row + col \in \{0, 2N-2\}$，索引为 row + col

``` c++
TC=O(N!)
SC=O(N)

class Solution {
public:
    int res;
    int totalNQueens(int n) {
        // 三种攻击方向
        vector<bool> hori(n), diag(2*n-1), anti(2*n-1);
        res = 0;
        bt(0, n, hori, diag, anti);
        return res;
    }
    
    void bt(int col, int n, vector<bool>& hori, vector<bool>& diag, vector<bool>& anti) {
        if (col == n) {
            res += 1;
            return;
        }
        
        for (int row = 0; row < n; row++) {
            // 三方向均安全
            if (hori[row] || diag[row + col] || anti[row - col + n - 1])
                continue;
            // 三方向设置为不安全
            hori[row] = diag[row + col] = anti[row - col + n - 1] = true;
            // 继续递归
            bt(col + 1, n, hori, diag, anti);
            // 回溯
            hori[row] = diag[row + col] = anti[row - col + n - 1] = false;
        }
    }
};
```

跟进一步可以用位运算代替，参考 [Short & Easy w/ Explanation & Visualization | Backtracking Explained!](https://leetcode.com/problems/n-queens-ii/discuss/1237811/Short-and-Easy-w-Explanation-and-Visualization-or-Backtracking-Explained!)

