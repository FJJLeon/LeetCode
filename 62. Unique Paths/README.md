# 62. Unique Paths

## 题目

题面：https://leetcode.com/problems/unique-paths/

一个 **m x n** 栅格，从左上角移动到右下角，只能向右或者向下，求所有可能的路径数。

## 思路与实现

### 1. 动态规划 & 空间优化

设 **dp[i][j]** 为从左上角到点 **(i,j)** 的路径数。

对于第一行和第一列的点，显然路径数只能为 1。而对于其他点，到达该点的路径只能来自于左边或者上边，因此有**dp[i][j] = dp[i-1][j] + dp[i][j-1]**。

实现中的小trick是可以创建一个 **(m+1)*(n+1)** 的动态规划矩阵，相当于在原栅格的左侧和上侧各扩展一格。

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // 此时左上角坐标是(1,1)，相当于认为入口在左上角的上方
        // 也可以写成 dp[1][1] = 1，但这样在循环中每次都要进行if判断
        dp[0][1] = 1;
        // Bottom-Up 填充 (1,1) - (m,n)
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m][n];
    }
};
```

如果不扩展一格，而使用 **m*n** 的DP矩阵，代码就会复杂些

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        // 填充第一列 (0,0)-(m-1,0) 为 1
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        // 填充第一行 (0,0)-(0,n-1) 为 1
        for (int j = 0; j < n; j++)
            dp[0][j] = 1;
        // 填充 (1,1)-(m-1,n-1)
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
```

优化空间使用，容易发现动态规划的转移方程每次只需要左边和上边的值，仅需要保存上一行的数据（上边），而左边的数据是在当前填充过程计算得到的，即仅需要维护两行数据。

更进一步，真的需要保留完整上一行数据吗？并不需要。在填充过程中，在点 **(i,j)** 处及本行之后的计算，只需要上一行 j 列及其右侧的数据 **[i-1, j : n]**，而左侧的数据已经用过了，不需要再用了。因此，只需要维护一行数据，当前行计算得到的结果直接覆盖即可。 

``` c++
TC=O(MN)
SC=O(min(M, N))，其实可以按行或者按列遍历，按小的那个比较好

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n + 1, 0);
        // 入口初始化
        dp[1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // dp[j] 上一行保存的数据，dp[j-1] 本行计算的数据
                // 直接覆盖
                dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[n];
    }
};
```

### 2. 组合数

本题的栅格中没有任何障碍，可以用组合数学直接计算。

从左上角 **(0,0)** 到右下角 **(m-1,n-1)** 一共需要 **m-1 + n-1** 步，其中有 **m-1** 步向下，**n-1** 步向右，因此，只要计算组合数 $m+n-2 \choose n-1$

``` c++
TC=O(min(M, N))
SC=O(1)

class Solution {
public:
    int uniquePaths(int m, int n) {
        int a = m+n-2, b = min(m-1, n-1);
        long long res = 1;
        for (int i = 1; i <= b; i++) {
            // 边乘边除，乘从 a-b+1 到 a，除从 1 到 b
            // 注意不能写成 res *= (a-b+i)/i，要先乘再除
            res = (res * (a-b+i)) / i;
        }
        return res;
    }
};
```
