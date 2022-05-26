# 354. Russian Doll Envelopes

## 题目

题面：https://leetcode.com/problems/russian-doll-envelopes/

给定了一组信封的宽和高，一个信封只有当宽和高都严格小于另一个信封时才能塞进去，问使用这组信封最多能套娃多少次。

## 思路与实现

### 1. 记忆化搜索，TLE

使用和 [329](../329.%20Longest%20Increasing%20Path%20in%20a%20Matrix/README.md) 题类似思路。将所有信封看作节点，可以套娃的信封之间存在有向边，从小的指向大的，形成一个有向无环图 DAG，在图中找到最长路径的长度即为可以套娃的次数。

``` c++
TC=O(N^2)
SC=O(N^2)

class Solution {
public:
    // 保存从信封 i 开始的最长路径长度
    vector<int> cache;
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        cache = vector<int>(n, -1);
        // 构建邻接表
        vector<vector<int>> adj(n, vector<int>());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 信封 i 可以塞进 信封 j，i -> j
                if (i != j && envelopes[i][0] < envelopes[j][0] && envelopes[i][1] < envelopes[j][1]) {
                    adj[i].push_back(j);
                }
            }
        }
        // 从每个信封开始 DFS，维护最长结果
        int res = INT_MIN;
        for (int i = 0; i < n; i++) {
            res = max(res, dfs(i, adj));
        }
        return res;
    }
    
    int dfs(int i, const vector<vector<int>>& adj) {
        // 已经访问过，直接返回
        if (cache[i] != -1)
            return cache[i];
        // 初始路径长度 1
        int num = 1;
        // 邻居 DFS
        for (int j : adj[i]) {
            num = max(num, dfs(j, adj) + 1);
        }
        // 记录结果
        cache[i] = num;
        return num;
    }
};
```

### 2. DP

这题和 329 题存在的本质差别是，329 题的点只能进行四邻域搜索，而本题的每个信封可以和其他任意信封比较搜索，这意味着本题的信封需要全局比较，而 329 题的点只有局部比较。因此可以进行全局排序。

首先，按照 width 对信封进行升序排序。对于每个信封，只有排在前面的 width 才小于或等于它，也才可能塞进去。用一维 DP 数组记录，二维循环转移，只有 width 和 height 同时小于才能塞进去从而更新 DP 数组。

``` c++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 1)
            return 1;
        // 按 width 升序
        sort(envelopes.begin(), envelopes.end());
        // 一维 DP 数组，dp[i] 记录最外层为信封 i 时的最多套娃层数
        vector<int> dp(n, 1);
        // i: 0 ~ n-1   j: 0 ~ i-1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 信封 j 可以塞进 i 里，动态规划转移
                if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        // 返回最大值
        return *max_element(dp.begin(), dp.end());
    }
};
```

然而，上述DP实现时间复杂度 O(N^2) 仍旧不能通过所有测试样例。

### 3. 基于 BinarySearch 的 LIS

问题实际上要求能够套娃的信封序列，在 width 和 height 两个维度上严格递增。同时做两个维度的控制很不直观，上述 DP 按 width 排序后实际上固定了 width 维度，但是题设的 width 是可以相等的，造成了 DP 过程仍旧不能忽略 width。

假如 width 互不相同，那么问题就变成了在对应的 height 序列上找 [最长递增子序列](/300.%20Longest%20Increasing%20Subsequence/README.md)，存在 O(NlogN) 解法。

但是现在 width 是可以相等的，显然会造成问题。若按 width 升序排序后，width 相等的信封 height 也正好递增排序，忽略 width 维度直接应用 LIS 解法就会把这些 width 相等的信封都选择而造成错误，实际上这些信封中最多只能选取一个。

很 tricky 的做法，在排序时，按照第一关键字 width 升序，第二关键字 height 降序，这样，width 相等的信封会按照 height 递减的顺序出现，LIS 算法只能从中选择最多一个，这样排序后再在 height 序列中找 LIS 即可。

``` c++
TC=O(NlogN)
SC=O(N)

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 1)
            return 1;
        // 按照 width 升序、height 降序进行排序
        sort(envelopes.begin(), envelopes.end(), [](vector<int>& e1, vector<int>& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
        });
        // LIS
        vector<int> sub;
        for (auto& e : envelopes) {
            // 找到第一个大于等于 e[1] 的迭代器，找不到则返回 end()
            auto iter = lower_bound(sub.begin(), sub.end(), e[1]);
            // 找不到，插入末尾
            if (iter == sub.end())
                sub.push_back(e[1]);
            // 找到了，则进行替换
            else
                *iter = e[1];
        }
        
        return sub.size();
    }
};
```

不用 STL

``` C++
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 1)
            return 1;
        
        sort(envelopes.begin(), envelopes.end(), [](vector<int>& e1, vector<int>& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
        });
        vector<int> dp(n);
        int size = 0;
        for (auto& e : envelopes) {
            int height = e[1];
            // 找到第一个大于等于 e[1] 的索引
            int l = 0, r = size;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (dp[mid] < height)
                    l = mid + 1;
                else
                    r = mid;
            }
            // 更新
            dp[l] = height;
            // 实际上没找到，是插入了新元素，扩展融合序列
            if (l == size)
                size++;
        }
        
        return size;
    }
};
```
