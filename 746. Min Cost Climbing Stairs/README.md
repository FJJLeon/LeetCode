# 746. Min Cost Climbing Stairs

## 题目

题面：https://leetcode.com/problems/min-cost-climbing-stairs/

从左到右爬楼梯，可以从 0 或 1 开始，每次可以爬一步或者两步，最后到达 n 位置（在数组外侧），问经过的最小花费。

## 实现

动态规划，令 dp[i] 表示从初始到达第 i 个位置的最小花费，则 **dp[i] = min(dp[i-1], dp[i-2]) + cost[i]**。最后的结果为 min(dp[n-1], dp[n-2])。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n);
        
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < n; i++) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        
        return min(dp[n-1], dp[n-2]);
    }
};
```

可以发现，转移过程只需要前面两个数字，因此可以进行空间优化。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int second = cost[0], first = cost[1];
        for (int i = 2; i < n; i++) {
            int t = cost[i] + min(second, first);
            second = first;
            first = t;
        }
        
        return min(second, first);
    }
};
```
