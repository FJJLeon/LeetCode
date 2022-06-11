# 1658. Minimum Operations to Reduce X to Zero

## 题目

题面：https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/

对于给定的数组，找到最短的前缀和加后缀和等于 x。

## 实现

如果暴力递归搜索的话会是指数级别的时间复杂度。

换一种思路，把数组前后连接看成一个环，要使得连接线处出现一个最短的子数组，其和为 x，等价于原数组中间要出现一个最长的子数组，其和为 sum(nums) - x，可以用滑动窗口解决。

### 1. 滑动窗口

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int target = 0, res = INT_MIN, sum = 0, n = nums.size();
        target = accumulate(nums.begin(), nums.end(), 0) - x;
        // 无法达成，直接返回
        if (target < 0)
            return -1;
        // 滑动窗口 [l, r]
        for (int l = 0, r = 0; r < n; r++) {
            // 窗口右扩，r 向右移动
            sum += nums[r];
            // 若窗口中的和大于 target，则 l 左移动，窗口缩小
            while (sum > target)
                sum -= nums[l++];
            // 若窗口中的和等于 target，则 res 更新
            if (sum == target)
                res = max(res, r - l + 1);
        }
        // 若存在满足的结果，则返回 n - res 为两侧的长度
        return res == INT_MIN ? -1 : n - res;
    }
};
```
