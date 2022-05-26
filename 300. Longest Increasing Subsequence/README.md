# 300. Longest Increasing Subsequence

## 题目

题面：https://leetcode.com/problems/longest-increasing-subsequence/

最长严格递增子序列 LIS

## 思路与实现

### 1. DP

动态规划，认为 **dp[i]** 表示以 nums[i] 结尾的 LIS[i] 长度，nums[i] 必须被选择。

计算过程中，遇到一个数 nums[i]，需要与前面的每个数 nums[j] (j < i) 比较，若 nums[j] < nums[i]，则 nums[i] 可以加到以 nums[j] 结尾的 LIS 后面，形成 dp[j] + 1 长度的 IS，选择最长的一个作为 LIS[i]，即

**dp[i] = max(dp[j]) + 1, j < i and nums[j] < nums[i]**

而整个序列的 LIS 长度为 **max(dp[i])**，选择每个位置结尾的LIS中最长的一个。

``` C++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        // 初始化 dp[0]
        dp[0] = 1;
        // i: 1 ~ n-1
        for (int i = 1; i < n; i++) {
            // 初始值，只有 nums[i] 自身
            dp[i] = 1;
            // 比较 j: 0 ~ i-1
            for (int j = 0; j < i; j++) {
                // 能形成更长的 LIS，更新
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
```

### 2. BinarySearch

基于二分查找的贪心求解，看题解才知道，不怎么直观，但是很有启发。

从例子解释，对于序列 **[1, 10, 7, 8, 3, 4, 5]**，在寻找 LIS 的过程中，从空递增子序列开始不断添加元素：

* 直到 10 都是递增的，子序列 sub1 = [1,10]
* 7 < 10，出现新分支序列 sub2 = [1,7]
* 继续选择，8无法放在 sub1 后面但可以放在 sub2 后面，sub2 = [1,7,8]，形成一个更长的 IS
* 3 < 8，形成一个新分支序列 sub3 = [1,3]
* 同样得，4、5 只能放在 sub3 后面，sub3 = [1,3,4,5]，得到最后的 LIS

在选择过程中我们维护了几个可复用的子序列，这导致了性能问题。从贪心的角度考虑，我们希望递增子序列能尽可能慢得递增，才能让子序列尽可能长。因此，我们只需要维护一个子序列 sub，这个子序列融合了每个存在的子序列，每个位置上只保留所有递增子序列中最小的那个；也就是说，**sub[i]** 表示所有长度为 i 的递增子序列中末尾元素最小值。

再看一遍栗子：

* 直到 10，融合序列 sub = [1,10]
* 7 < 10，新序列 [1,7]，因此融合序列中 10 被 7 替换，sub = [1,7]
* 继续选择，sub = [1,7,8]
* 3 < 8，新序列 [1,3]，因此融合序列中 7 被 3 替换，sub = [1,3,8]
* 继续选择，sub = [1,3,4,5] 即为最后的 LIS

值得注意的是，融合序列中有一个 [1,3,8] 很不直观，3 是在 8 后面出现的，但在序列中出现在了 8 前面。所以需要着重理解融合序列的定义，每个元素不保证原序列的出现顺序，3 是子序列 [1,3] 的末尾元素，8 是子序列 [1,7,8] 的末尾元素，融合序列中可以破坏原本序列中的前后顺序，但保证大小关系。

融合序列同样是个递增序列，因此可以使用二分搜索找到潜在的需要被替换元素，从而降低整体复杂度。

Reference：
* [[C++/Python] DP, Binary Search, BIT Solutions - Picture explain - O(NlogN)](https://leetcode.com/problems/longest-increasing-subsequence/discuss/1326308/C%2B%2BPython-DP-Binary-Search-BIT-Solutions-Picture-explain-O(NlogN))
``` C++
TC=O(NlogN)
SC=O(N)

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> sub;
        for (int i = 0; i < n; i++) {
            // 在融合序列中找到第一个大于等于 nums[i] 的迭代器，没有则返回 end()
            auto iter = lower_bound(sub.begin(), sub.end(), nums[i]);
            // 没有，融合序列增长
            if (iter == sub.end())
                sub.push_back(nums[i]);
            // 有，替换
            else
                *iter = nums[i];
        }
        
        return sub.size();
    }
};
```

不用 STL 函数

``` C++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // 直接固定融合序列大小，用 size 表示使用到的长度
        vector<int> sub(n, 0);
        int size = 0;
        for (int i = 0; i < n; i++) {
            // 融合序列空，或 nums[i] 大于融合序列末尾元素
            if (size == 0 || sub[size - 1] < nums[i]) {
                // 直接扩展
                sub[size++] = nums[i];
            }
            else {
                // 二分搜索 第一个大于等于 nums[i] 的索引
                int l = 0, r = size;
                while (l < r) {
                    int mid = l + (r - l) / 2;
                    if (sub[mid] < nums[i])
                        l = mid + 1;
                    else
                        r = mid;
                }
                // 替换
                sub[l] = nums[i];
            }
        }
        
        return size;
    }
};
```
