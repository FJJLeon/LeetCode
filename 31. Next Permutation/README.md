# 31. Next Permutation

## 描述

题面：https://leetcode.com/problems/next-permutation/

给定一个数字数组，找到其全排列数组集合中字典序的下一个数组。比如 **[1,2,3,5,4]** 的下一个排列是 **[1,2,4,3,5]**。

那么如何找到下一个排列，从右往左找到第一个谷值 d，其右边是递减序列。在序列找到第一个大于谷值的数 r，交换两者，并翻转新的递减序列。

特别的，**[5,4,3,2,1]** 的下一个认为是 **[1,2,3,4,5]**

## 思路与实现

``` c++
TC = O(N)
SC = O(1)

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), d = n - 2;
        if (n == 1)
            return;
        // 以 nums = [1,2,3,5,4] 为例
        // 从后往前找到第一个谷，在 nums[d]=3, nums[d+1]=5 时停止，谷值为 nums[d]=3, d=2
        while (d >= 0 && nums[d] >= nums[d + 1])
            d--;
        // d >= 0，说明谷值存在
        if (d >= 0) {
            int r = n - 1;
            // 从后往前，找到第一个大于（不能等于）谷值的，即 nums[r]=4
            while (nums[r] <= nums[d])
                r--;
            // 交换 nums[d] 和 nums[r]
            swap(nums[r], nums[d]);
        }
        // 交换完成后的数位数组已经比原来的大，但不是最接近的
        // 新谷值往后的的递减序列本身是最大的排列
        // 逆序之即可
        // 若是特殊情况全递减数组，也可以同时逆序得到结果
        reverse(nums.begin() + d + 1, nums.end());
        return;
    }
};
```

