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

基于01背包的DP还能进行优化，以上DP的整个过程都维护了总和一半大小的数组，实际上在迭代中对于目前无法得到的和可以不进行维护，即只使用一个集合保存使用目前迭代到的数可以得到的和。

Python 代码如下：
* Time: O(n*sum/2)
* Space: O(sum/2)
``` python
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        s = sum(nums)
        if (s & 1):
            return False
        target = s >> 1
        possible_sums = {0}
        for n in nums:
            possible_sums.update({(v + n) for v in possible_sums})
            if target in possible_sums:
                return True
        return target in possible_sums  
```

使用相同逻辑的C++代码如下，但仅使用 set 或者 unordered_set 实现会花费大量时间在更新集合并做集合并操作上。
也可能是我没有想到正确的写法

* Time: O(n*sum/2), 692 ms
* Space: O(sum/2), 120.6 MB
``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;
        int half = sum >> 1;
        unordered_set<int> s{0}, t;
        for (int& n : nums) {
            for (int v : s) {
                if (v + n <= half)
                    t.insert(v + n);
            }
            if (t.find(half) != s.end())
                return true;
            set_union(s.begin(), s.end(), t.begin(), t.end(), inserter(s, s.begin()));
            t.clear();
        }
        
        return s.find(half) != s.end();
    }
};
```

而在讨论区中发现的神奇利用了 bitset，创建一个足够大小的bitset，其中每一位代表使用当前数据是否可以得到该位的和，利用 bitset 保存集合，并迭代完成集合更新。

* Time: O(n), 12 ms 时间复杂度存疑
* Space: O(sum/2), 9.2 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;
        int half = sum >> 1;
        
        bitset<20001> bs(1);
        for (int& n : nums)
            bs |= bs << n;
        
        return bs.test(half);
    }
};
```

### DFS暴力搜索优化

纯粹简单的DFS暴力搜索尝试所有可能必然超时。
在 dfs 函数中，currIdx 表示当前搜索使用的数组索引，remain 表示使用包括当前索引在内的 [currIdx, end] 数组还需要得到的和。

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        cout << nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;

        return dfs(nums, 0, sum >> 1);
    }
    
    set<int> visited;
    
    bool dfs(vector<int>& nums, int currIdx, int remain) {
        if (remain == 0) {
            return true;
        } else if (remain < 0) {
            return false;
        }

        for (int i = currIdx; i < nums.size(); i++) {
            if (dfs(nums, i + 1, remain - nums[i])) {
                return true;
            }
        }
        
        return false;
    }
};
```

但DFS过程中，我们可以保存历史尝试来进行大胆的剪枝。
剪枝基于的逻辑如下：
* 首先对于同一个 currIdx 来说，若曾经尝试过某个 remain 值，后来再遇到则可以直接返回，必然同样无法完成。
* 在 DFS 的搜索顺序下，在小于 currIdx 的索引处尝试的某个 remain 值，若在 currIdx 处遇到，那仍然无法完成。小于 currIdx 的索引时执行的 DFS 使用了比 currIdx 更多的数，无法得到 remain 和；现在 currIdx 使用更少的数，更加无法得到 remain 和。

* Time: O(sum/2), 12 ms，最多尝试 sum/2 次
* Space: O(sum/2), 9.7 MB

``` c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if (sum & 1)
            return false;

        return canSum(nums, 0, sum >> 1);
    }
    
    set<int> visited;
    
    bool canSum(vector<int>& nums, int currIdx, int remain) {
        if (remain == 0) {
            return true;
        } else if (remain < 0) {
            return false;
        }
        
        if (visited.find(remain) != visited.end())
            return false;
        // 保存历史尝试
        visited.insert(remain);

        for (int i = currIdx; i < nums.size(); i++) {
            if (canSum(nums, i+1, remain - nums[i])) {
                return true;
            }
        }
        
        return false;
    }
};
```
