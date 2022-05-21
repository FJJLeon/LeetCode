# 322. Coin Change

## 题目

题面：https://leetcode.com/problems/coin-change/

有一堆不同面值的硬币 coins，每种面值无限枚，问最少需要多少枚能得到 amount 金额。

## 实现

动态规划，令 **dp[n]** 表示组成金额 n 最少需要的硬币数量。那么自底向上的动态规划求解

$dp[n] = 1 + min(dp[n - c]), c \in coins, n \geq c$

``` c++
TC=O(NC), N = amount, C = len(coins)
SC=O(N)

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 升序排列 coins
        sort(coins.begin(), coins.end());
        // 初始化组成所需为 INT_MAX - 1，其实只要 amount + 1 即可
        // 但不能是 INT_MAX，会 overflow
        vector<int> dp(amount + 1, INT_MAX - 1);
        // 入口初始化
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int c : coins) {
                if (i >= c)
                    dp[i] = min(dp[i], 1 + dp[i - c]);
                // 剪枝优化，升序排列后遇到大于 i 的硬币面额即可停止
                else
                    break;
            }
        }
        
        return dp[amount] == INT_MAX - 1 ? -1 : dp[amount];
    }
};
```
