# 1695. Maximum Erasure Value

## 题目

题面：https://leetcode.com/problems/maximum-erasure-value/

对于给定的数组，求出其中元素唯一的子数组和的最大值。

## 实现

滑动窗口维护子数组，保证数组中的元素唯一。

两种不同的实现，一种用 set 维护元素在窗口中是否出现过，一种用 map 维护元素在窗口中最近出现时的索引。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size(), res = INT_MIN;
        // 用 set 维护元素在窗口中是否出现过
        unordered_set<int> seen;
        // 维护窗口 [l, r]
        for (int l = 0, r = 0, score = 0; r < n; r++) {
            // 当前元素在窗口中出现过，则窗口缩小，l 向右移动
            while (seen.count(nums[r])) {
                score -= nums[l];
                seen.erase(nums[l++]);
            }
            // 窗口右扩，r 向右移动
            score += nums[r];
            seen.insert(nums[r]);
            // 更新长度 res
            res = max(res, score);
        }
        
        return res;
    }
};
```

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size(), res = INT_MIN;
        // 用 map 维护元素在窗口中最近出现时的索引
        unordered_map<int, int> lastIdx;
        for (int l = 0, r = 0, score = 0; r < n; r++) {
            // 当前元素在窗口中出现过，找到最近出现的索引
            auto it = lastIdx.find(nums[r]);
            // 索引存在
            if (it != lastIdx.end()) {
                // 窗口缩小，l 向右移动直到 idx 右侧
                int idx = it->second;
                while (l <= idx) {
                    score -= nums[l++];
                }
            }
            score += nums[r];
            lastIdx[nums[r]] = r;
            res = max(res, score);
        }
        
        return res;
    }
};
```
