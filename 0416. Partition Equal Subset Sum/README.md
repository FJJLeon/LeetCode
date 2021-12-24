# 416. Partition Equal Subset Sum

## Description

[Leetcode题面](https://leetcode.com/problems/partition-equal-subset-sum/)

给定正整数数组，能否分成两个和相等的子集

## Solution

### 暴力搜索1

对数组中的每个数，选择或不选择，判断选择的数求和是否等于全局和的一半

* Time：TLE, O(2^n)
* Space：O(1)

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;
        int half = sum >> 1;

        return search(nums, 0, half);
    }
private:   
    bool search(vector<int>& nums, int cur, int remain) {
        if (remain == 0)
            return true;
        if (cur == nums.size() || remain < 0)
            return false;
        
        return search(nums, cur + 1, remain) || search(nums, cur + 1, remain - nums[cur]);
    }
};
```

### 暴力搜索2

对数组中的每个数，要么加要么减，最后的结果为零则能分成两个等和子集。
暴力搜索，将加或者减后的结果加入一个集合，用下一个数迭代更新。
需要注意的是，更新时只需要记录所有非负数即可，负数可以由反转前面所有正负号得到。

此暴力搜索没有递归，优化掉了负数，在LeetCode的测评中结果为 `117 / 117 test cases passed, but took too long.` 通过所有测试但花费太长时间，第一次见到这样的结果。而递归暴力搜索直接无法通过所有测试。

* Time：TLE, O(2^n)
* Space：O(2^n)

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        unordered_set<int> s;
        s.insert(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            unordered_set<int> t;
            // update set by +/- each item
            for (int n : s) {
                t.insert(abs(n + nums[i]));
                t.insert(abs(n - nums[i]));
            }
            s = t;
        }
        
        return s.find(0) != s.end();
    }
};
```

### DP

#### DP - 0/1背包

Subset Sum 转化为 0/1 背包。
数组中每个数 n，都认为是一件容量为 n ，价值也为 n 的物品，放到一个大小为 w = sum / 2 的背包中，若能放满即得到的物品价值最大也为 w，则存在对应的数组划分。
* `dp[i][j]` 代表使用前 i 个物品，放进大小为 j 的背包中所能获得的最大价值
* 转移方程：`dp[i][j] = max(dp[i-1][j], dp[i-1][j-t] + t)`，其中 t 为第 i 件物品的大小（价值）
* 若 `dp[n][w] == w`，则存在对应的数组划分

* Time: O(n*sum/2), 204 ms
* Space: O(n*sum/2), 76 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for (int& n : nums)
            sum += n;
        if (sum & 1)
            return false;
        int w = sum / 2;
        
        vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            int t = nums[i-1];
            for (int j = 1; j <= w; j++) {
                if (j >= t)
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-t] + t);
                else
                    dp[i][j] = dp[i-1][j];
            }
        }
        
        return dp[n][w] == w;
    }
};
```

#### DP - 空间优化

* 0/1 背包的空间复杂度优化，转移方程 `dp[j] = max(dp[j], dp[j-t] + t)`, 其中 t 为当前数。
* 每次迭代时其实只需使用上一件物品的dp，保存成两行即可。
* 由于背包问题的转移方程只需要用到 j 更小的数据，可以倒序更新，只保存一行dp。
  
* Time: O(n*sum/2), 108 ms
* Space: O(sum/2), 10 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for (int& n : nums)
            sum += n;
        if (sum & 1)
            return false;
        int w = sum / 2;
        
        vector<int> dp(w + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            int t = nums[i-1];
            for (int j = w; j >= t; j--) {
                dp[j] = max(dp[j], dp[j-t] + t);
            }
        }
        
        return dp[w] == w;
    }
};
```

#### DP 转换视角

前面 DP 过程是以0/1背包的视角来迭代的，实际上可以直接由本题的视角来迭代

* 注意前面解法最后的判断 `dp[w] == w`，其中 w 为背包大小。能放满即表示当前物品中可以选出子集，其和等于 w，则存在对应的数组划分。那么在DP中直接保存这个能否放满的判断即可。
* 因此，改变 DP 保存的表，`dp[i][j]` 表示前 i 个数字能否得到和 j。
* 转移方程: `dp[i][j] = dp[i-1][j] | dp[i-1][j-t]`，其中 `t = nums[i-1]` 为当前数，此处 `i-1` 是考虑DP数组第一行第一列。
* `dp[i][j]` 为 true，要么前 i - 1 项已经能得到和 j，即 `dp[i-1][j] = true`；要么前 i - 1 项能得到和 j - t，加上第 i 项 t 就得到和 j，即 `dp[i-1][j-t] = true`。

* Time: O(n*sum/2), 228 ms
* Space: O(n*sum/2), 11.9 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;
        int w = sum >> 1;
        
        vector<vector<bool>> dp(n + 1, vector<bool>(w + 1, false));
        // sum = 0, must true
        for (int i = 0; i <= n;i++) 
            dp[i][0] = true;
        
        for (int i = 1; i <= n; i++) {
            int t = nums[i-1];
            for (int j = w; j >= 0; j--) {
                if (j >= t)
                    dp[i][j] = dp[i-1][j] | dp[i-1][j-t];
                else
                    dp[i][j] = dp[i-1][j];
            }
        }
        
        return dp[n][w];
    }
};
```

#### DP 转换视角后空间优化

* Time: O(n*sum/2), 92 ms
* Space: O(sum/2), 9.1 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;
        int w = sum >> 1;
        
        vector<bool> dp(w + 1, false);
        // sum = 0, must true
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            int t = nums[i-1];
            for (int j = w; j >= t; j--) {
                dp[j] = dp[j] | dp[j-t];
            }
        }
        
        return dp[w];
    }
};
```

### DP 使用bitset

### DFS