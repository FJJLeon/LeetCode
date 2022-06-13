# 120. Triangle

## 题目

题面：https://leetcode.com/problems/triangle/

一个金字塔三角形，当前层 i 位置可以走到下一层的 i 和 i+1 位置，只能往下走，求出和最小的路径，返回该值。

## 实现

显然动态规划，或者记忆化搜索。

如果我们用二维DP数组，**dp[i][j]** 表示走到 i 层 j 位置的最小路径和，那么转移方程为 **dp[i][j] = min(dp[i-1][j-1] + dp[i-1][j]) + triangle[i][j]**，即上一层（i-1）的 j 位置和 j-1 位置可以走到 (i,j) 位置。另外，注意边界条件，每层的开始位置和末尾位置只有一个可能来源。

注意到，每层动态规划时实际上只用到了上一层靠左（j 较小）的数据，所以可以用一维数组逆向计算来实现。

即用一维数组 **dp[j]** 表示走到某层的 j 位置的最小路径和，从第 i = 0 层往下，从右往左计算，转移方程为 **dp[j] = min(dp[j-1], dp[j]) + triangle[i][j]**。

``` c++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n, 0);
        // 第一层
        dp[0] = triangle[0][0];
        // 从第 1 层到最后一层
        for (int i = 1; i < n; i++) {
            // 从右往左计算
            // 最右，j = i
            dp[i] = dp[i - 1] + triangle[i][i];
            // 从右往左，j: i-1 ~ 1
            for (int j = i - 1; j > 0; j--) {
                dp[j] = min(dp[j-1], dp[j]) + triangle[i][j];
            }
            // 最左，j = 0
            dp[0] += triangle[i][0];
        }
        // 取最小值
        return *min_element(dp.begin(), dp.end());
    }
};
```

实际上，空间优化过程跳过了一段，我们可以使用两个一维数组，用层数的奇偶性选择上一层的数据，类似ping-pong，空间 O(2N)，参考[三角形最小路径和](https://leetcode.cn/problems/triangle/solution/san-jiao-xing-zui-xiao-lu-jing-he-by-leetcode-solu/)。

查看题解，发现从底层想顶层计算，对边界计算是统一的，代码上可以更优雅。

``` c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // 初始化 dp 数组为最后一层
        vector<int> dp(triangle.back());
        // 从底层往顶层计算
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};
```
