# 1696. Jump Game VI

## 题目

题面：https://leetcode-cn.com/problems/jump-game-v/

跳跃游戏系列第 6 题，从 0 开始，一次最多可以跳 k 步，不能跳出边界，目标是跳到 n-1 处，问这个过程中走过的位置之和的最大值。

## 思路与实现

显然是动态规划，贪心会陷入局部最优。

令 **dp[i]** 表示从 0 开始走到 i 处所能获取的最大得分，则有：

$$dp[i] = max\{ dp[j] \} + nums[i], max(0, i-k) \leq j < i$$

从左到右计算DP数组即可。当然也可以反过来想，认为 dp[i] 表示从 i 处走到 n-1 处所能获取的最大得分，则有：

$$dp[i] = max\{ dp[j] \} + nums[i], i < j \leq min(i+k, n-1)$$

此时需要从右向左计算。

### 1. 直接 DP

以下解法是反向计算的

``` c++
TC=O(NK)
SC=O(N)

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        dp[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            int cur = INT_MIN, reach = min(n - 1, i + k);
            for (int j = i+1; j <= reach; j++) {
                cur = max(cur, dp[j]);
            }
            dp[i] = cur + nums[i];
        }
        
        return dp[0];
    }
};
```

然而，O(NK)的时间复杂度会超时。

### 2. DP + 优先队列PQ

在每次计算 dp[i] 时，其实不需要把待选的上一步值都遍历一遍找到最大值（花费 O(K) 的时间），可以使用优先队列直接获取该值，O(logN)。

值得注意的是，对于 k 步之外的值，需要从队列中删除。因此队列中需要保存DP对应的索引值，由两种方式，要么保存 **{dp[j], j}** pair，要么只保存索引值。我选择保存 pair，那么动规数组就不需要了，DP值在队列中，只需要更新一个步进的结果即可。

``` c++
TC=O(NlogN), 最差情况PQ会保存所有值
SC=O(N)

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        
        int res = nums[0];
        priority_queue<pair<int, int>> pq;
        pq.push({res, 0});
        for (int i = 1; i < n; i++) {
            while (pq.top().second < i - k)
                pq.pop();
            res = pq.top().first + nums[i];
            pq.push({res, i});
        }
        
        return res;
    }
};
```

### 3. DP + 单调队列

更进一步，可以使用索引的单调队列进行优化。优先队列中实际上保存了大量无用值，我们实际上需要保存的是更大且更接近当前索引的值。

什么意思呢，考虑两个索引 j 和 k, 有 j < k，且状态 dp[j] <= dp[k]，那么在 k 之后的状态转移计算中，j 的状态是不需要被使用的。因为存在 k 这个索引更大（更靠右边，能在滑动窗口中保留更久）且值不比 j 差的状态，后续的转移计算只会用 k 或者比 k 更优的状态，所以 j 的状态不需要被使用。

因此，在我们计算到 k 处时，可以直接将 j 的状态从队列中删除，从而在后续计算中保证第一个合法状态（在窗口中）即为当前窗口最优值。

由于队列需要支持从前和后删除，使用双端队列实现。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        
        int res = nums[0];
        // {dp[j], j} - {状态，索引}
        deque<pair<int, int>> dq;
        dq.push_back({res, 0});
        for (int i = 1; i < n; i++) {
            // 队首的索引不合法，已经不在当前窗口中，删除
            while (dq.front().second < i - k)
                dq.pop_front();
            // 当前索引的状态
            res = dq.front().first + nums[i];
            // 队尾的状态值不优于当前状态，删除，只需要保留 值更大且索引更靠右 的状态即可
            while (!dq.empty() && dq.back().first <= res)
                dq.pop_back();
            // 当前状态进入队尾
            dq.push_back({res, i});
        }
        
        return res;
    }
};
```
为什么复杂度直接降低到了线性呢，从整体考虑，所有元素只会在 deque 中进出各一次，所以复杂度为 O(N)。
