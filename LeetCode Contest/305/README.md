# 周赛 305

20220807

## [T1, 2367. 算术三元组的数目](https://leetcode.cn/problems/number-of-arithmetic-triplets/)

计算满足条件的三元组的数目，三元组索引递增，依次数值差均等于 diff。

### 1. Set

对于每个 nums[k]，判断是否存在对应的 i,j

``` c++
TC=O(NlogN) - set / O(N) - unordered_set
SC=O(N)

class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int n = nums.size();
        int count = 0;
        set<int> s;
        for (int i = 0; i < n; i++) {
            if (s.count(nums[i] - diff) && s.count(nums[i] - 2 * diff)) {
                count++;
            }
            s.insert(nums[i]);
        }
        return count;
    }
};
```

### 2. 三指针

考虑到数组的严格递增，对于每个 nums[k]，j、i 指针依次右移

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int res = 0, i = 0, j = 1;
        for (int nk : nums) {
            // j 右移
            while (nums[j] + diff < nk) j++;
            // j 已经不满足 diff
            if (nums[j] + diff > nk) continue;
            // i 右移
            while (nums[i] + 2 * diff < nk) i++;
            // 找到一个三元组
            if (nums[i] + 2 * diff == nk) res++;
        }
        return res;
    }
};
```

## [T2. 2368. 受限条件下可到达节点的数目](https://leetcode.cn/problems/reachable-nodes-with-restrictions/)

一颗 N 点 N-1 边的无向树，存在受限节点是不可访问的，问从 0 节点可到达的所有节点数量

### 有限制的 BFS / DFS

在普通的图遍历中加入了不可访问的受限节点，多使用一个集合来记录不可访问的节点进行判断即可。

``` c++
TC=O(N)，只有 N 点 N - 1 边
SC=O(N)

class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        // 建图
        vector<vector<int>> graph(n, vector<int>());
        for (auto& e : edges) {
            // 无向边
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        // 受限节点
        set<int> rest(restricted.begin(), restricted.end());
        // 已遍历节点
        set<int> vis;
        // 基于 Queue 的 BFS
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            vis.insert(cur);
            for (int next : graph[cur]) {
                // 除了已访问节点，还需要判断受限节点
                if (rest.count(next) == 0 && vis.count(next) == 0)
                    q.push(next);
            }
        }
        return vis.size();
    }
};
```
小优化：使用 unordered_set 保存受限节点以及使用 vector 保存已访问节点

## [T3. 2369. 检查数组是否存在有效划分]

问数组是否能划分成满足条件的几个连续子数组，条件包括：
* 两个数的数组，两个数相等
* 三个数的数组，三个数相等
* 三个数的数组，相邻数差值为 1

### 序列DP

动态规划，从左往右计算每个位置的状态，每个位置的状态可以由前两个位置或前三个位置处的状态转移而来，根据条件进行或运算。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        // 实现时多加一个 0 位置的 true 值，便于边界处理。
        vector<int> dp(n + 1);
        dp[0] = true;
        // 一个数和两个数的情况直接赋值
        dp[1] = false;
        dp[2] = (nums[0] == nums[1]);
        for (int j = 3; j <= n; j++) {
            int i = j - 1; // i 为nums数组索引，j 为DP索引
            dp[j] = (dp[j-2] && (nums[i-1] == nums[i]) ) ||
                    (dp[j-3] && (nums[i-2] == nums[i-1]) && (nums[i-1] == nums[i])) ||
                    (dp[j-3] && (nums[i-2] + 1 == nums[i-1]) && (nums[i-1] + 1 == nums[i]));
        }
        return dp[n] ? true : false;
    }
};
```

显然可以进行空间优化，只需要左边两个状态即可

## [T4. 2370. 最长理想子序列](https://leetcode.cn/problems/longest-ideal-subsequence/)

给定字符串，求满足条件的最长理想子序列长度，
* 子序列相邻字符在字母表中的位次的绝对差值小于等于给定的 k

### 1. 暴力动态规划, TLE

求的是子序列，可以不连续，那么考虑使用动态规划。令 dp[i] 是以 s[i] 结尾的理想子序列长度，可以遍历字符串中的字符 s[j] (0 <= j < i) ，若 s[i] 和被比较字符 s[j] 的绝对差值小于等于 k，则以 s[j] 结尾的理想子序列可以依靠 s[i] 延长 1，即

$$dp[i] = max\{dp[j], 0 \leq j < i, \ \text{abs}(s[i] - s[j]) <= k \}$$

``` c++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        // 多加一个 0 位置长度为 0 的序列，便于边界处理。
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        // 最大值
        int res = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (j == 0 || abs(s[i-1] - s[j-1]) <= k) {
                    // 动态规划转移
                    dp[i] = max(dp[i], dp[j] + 1);
                    // 更新最大值
                    res = max(res, dp[i]);
                }
            }
        }
        return res;
    }
};
```

### 2. 优化动态规划

上述提到的动态规划转移方程中，每次转移都需要与前面所有的子序列相比较，时间复杂度 O(N)。能否进行优化？

赛中一直在试图记录每个子序列的最长长度，陷入了误区。仅使用了 map 维护所有独立子序列，即以某个索引处字符结尾的独立理想子序列长度，转移时仅比较这些独立子序列。但是独立子序列是错误的，独立理想子序列仅仅维护了之前局部的最长，不能计算到全局最长。比如某个独立子序列 [7,10,15], 但是后续有字符 [9,8], k = 5，那么后续的字符就无法接到 15 后面，但是能接到 10 后面形成 [7,10,9,8] 这个更长的理想子序列。后来又想到上面的问题在于只记录了 10 - 15 这一升序的延长方式，还需要记录一个降序的延长方式，但是这样做复杂度持续上升。最后看着这小写字母才恍然大悟只要**记录各个小写字母结尾的最长理想子序列**即可，简单且不会有遗漏，实现每次转移的时间复杂度 O(26)=O(1)，还是题做少了。

``` c++
TC=O(N*K)
SC=O(N)

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        // 使用 vector 记录以每个小写字母结尾的最长理想子序列长度
        vector<int> ch2len(26);
        int res = -1;
        for (int i = 1; i <= n; i++) {/
            // 遍历字符 s[i-1] 左右 k 位次，进行转移
            int l = max(0, s[i-1] - 'a' - k), r = min(26, s[i-1] - 'a' + k + 1);
            for (int c = l; c < r; c++) {
                dp[i] = max(dp[i], ch2len[c] + 1);
            }
            ch2len[s[i-1] - 'a'] = dp[i];
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

可以发现长度 O(N) 的动态规划数组是没有用的，我们只需要记录每个小写字母结尾的最长理想子序列长度即可进行后续转移。

``` c++
TC=O(N*K)
SC=O(1)

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        vector<int> dp(26);
        int res = -1;
        for (char ch : s) {
            int cur = ch - 'a';
            int l = max(0, cur - k), r = min(26, cur + k + 1), cnt = 0;
            for (int c = l; c < r; c++) {
                // 注意不能在内部更新 dp[cur]，此时求的是之前的最长理想子序列
                // dp[c] 需要使用旧数据
                cnt = max(cnt, dp[c]);
            }
            // 以 ch 结尾的最长理想子序列延长 1
            dp[cur] = cnt + 1;
            res = max(res, dp[cur]);
        }
        return res;
    }
};
```
