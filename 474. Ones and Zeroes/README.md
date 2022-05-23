# 474. Ones and Zeroes

## 题目

题面：https://leetcode.com/problems/ones-and-zeroes/

## 思路与实现

咋一看觉得是动态规划，但是又不能分析出明确的子问题，看了一眼题解标题发现写着 01背包，棋差一招满盘皆输。

什么意思呢，其实是有两个限制条件的 01 背包。认为每个字符串是一件物品，0 的个数为重量，1 的个数为体积，每个物品只有一个，放进能容纳 m 重量 n 体积的背包中，问最多能放几个物品。

这样就需要创建一个三维动态规划数组 **dp[k][i][j]** 代表使用前 k 个字符串，在最多 i 个 0 和 j 个 1 的限制下，能最多放入的字符串数量。转移方程:

$dp[k][i][j] = max(dp[k-1][i][j], dp[k-1][i-zeros(k)][j-ones(k)]+1$

其中 zeros(k), ones(k) 代表第 k 个字符串中 0 和 1 的个数。就是说，对于计算 dp[k][i][j]，我们已然知道子问题使用前 k-1 个字符串的所有解即 dp[k-1][0][0] ~ dp[k-1][m][n]，那么问题只在于第 k 个字符串到底是选还是不选。如果选，那么就需要用 dp[k-1][i-zeros(k)][j-ones(k)] + 1；如果不选，那么就是 dp[k-1][i][j]。选择较大的那个作为结果。

``` c++
TC=O(LMN)
SC=O(LMN)

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        int dp[len+1][m+1][n+1];
        memset(dp, 0, sizeof(dp));
        // 对于每个字符串，选或者不选
        for (int k = 1; k <= len; k++) {
            // 计算 0 1 的个数
            int zeros = 0, ones = 0;
            for (char c : strs[k-1]) {
                if (c == '0')
                    zeros++;
                else
                    ones++;
            }
            // 0\1 个数的限制条件
            for (int i = 0; i <= m; i++) {
                for (int j = 0; j <= n; j++) {
                    // 0 1 个数可以满足条件，用 选、不选 第k个字符串中较大的那个作为结果
                    if (zeros <= i && ones <= j) {
                        dp[k][i][j] = max(dp[k-1][i][j], dp[k-1][i-zeros][j-ones] + 1);
                    }
                    // 不满足条件，第 k 个字符串就无法选择，只能不选
                    else {
                        dp[k][i][j] = dp[k-1][i][j];
                    }
                }
            }
        }
        
        return dp[len][m][n];
    }
};
```

01背包可以去掉物品选择那一维度，然后倒序循环限制条件，从而在满足转移方程推导的前提下优化空间复杂度。

``` c++
TC=O(LMN)
SC=O(MN)

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        int dp[m+1][n+1];
        memset(dp, 0, sizeof(dp));
        
        for (int k = 1; k <= len; k++) {
            int zeros = 0, ones = 0;
            for (char c : strs[k-1]) {
                if (c == '0')
                    zeros++;
                else
                    ones++;
            }
            // 注意需要倒序，转移方程需要用到 i j 较小的上一轮数据，若仍正序则会被提前覆盖
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
                }
            }
        }
        
        return dp[m][n];
    }
};
```