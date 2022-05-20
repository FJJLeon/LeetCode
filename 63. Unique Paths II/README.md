# 63. Unique Paths II

## 题目

题目：https://leetcode.com/problems/unique-paths-ii/

[62. Unique Paths](https://leetcode.com/problems/unique-paths/) 题的扩展，栅格中存在障碍。

## 思路与实现

栅格存在障碍仍旧可以用类似的动态规划方法解决，设 **dp[i][j]** 为从左上角到点 **(i,j)** 的路径数。

若点 **(i,j)** 没有障碍，那么转移方程不变，仍为 **dp[i][j] = dp[i-1][j] + dp[i][j-1]**；若有障碍，那么 **dp[i][j]=0**。

仍可扩展一格，创建一个 **(m+1)*(n+1)** 的动态规划矩阵。

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // 此时左上角坐标是(1,1)，相当于认为入口在左上角的上方
        // 也可以写成 dp[1][1] = 1，但这样在循环中每次都要进行if判断
        dp[0][1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // (i,j)无障碍，按转移方程填充
                if (!obstacleGrid[i-1][j-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
                // 默认初始化为 0，可以不操作
                // else {
                //     dp[i][j] = 0;
                // }
            }
        }
        return dp[m][n];
    }
```

空间优化

``` c++
TC=O(MN)
SC=O(N)

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<int> dp(vector<int>(n + 1, 0));
        // 入口初始化
        dp[1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // dp[j] 上一行保存的数据，dp[j-1] 本行计算的数据
                // 进行覆写
                if (!obstacleGrid[i-1][j-1])
                    dp[j] = dp[j-1] + dp[j];
                else // 这个必须操作，需要把上一行数据覆写
                    dp[j] = 0;
            }
        }
        return dp[n];
    }
};
```