# 665. Non-decreasing Array

## 题目

题面：https://leetcode-cn.com/problems/non-decreasing-array/

对于给定的数组，最多修改一个元素，能否使其非降。

## 实现

思路很容易想到，就是从左到右遍历进行比较，当发现一个降序对的时候，进行修改。那么如何修改呢？当发现一个 i 不满足条件时，即 num[i-1] > nums[i]，为了后续的数组非降，我们总是希望减小 nums[i-1] 到 nums[i] 使得尽可能满足后续的非降；但是，减小 nums[i-1] 却可能破坏靠前的非降对，即加入 nums[i] 不仅比 nums[i-1] 小，同时还比 nums[i-2] 小，那么此时只能作增大 nums[i] 的修改。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        bool canModify = true;
        for (int i = 1; i < nums.size(); i++) {
            // 发现降序，需要修改操作
            if (nums[i] < nums[i-1]) {
                // 还可以进行修改操作
                if (canModify) {
                    // 只允许一次修改操作
                    canModify = false;
                    // nums[i] 比 nums[i-2] 大，则减小 nums[i-1]
                    if (i < 2 || nums[i] >= nums[i-2])
                        nums[i-1] = nums[i]; // 这里其实无需操作
                    // nums[i] 比 nums[i-2] 小，则需要增大 nums[i]
                    else
                        nums[i] = nums[i-1];
                }
                // 已修改过
                else
                    return false;
            }
        }
        
        return true;
    }
};
```

以上过程修改了输入数组，可以用一个临时变量保存上一个元素而不修改输入数组

``` c++

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        bool canModify = true;
        // 保存上一个元素，可以是修改后的元素（但不修改输入数组）
        int last = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < last) {
                if (canModify) {
                    canModify = false;
                    // nums[i] 比 nums[i-2] 大，则需要减小 nums[i-1]，但这不影响下次比较时 last 的值
                    if (i < 2 || nums[i] >= nums[i-2])
                        last = nums[i];
                    // nums[i] 比 nums[i-2] 小，则需要增大 nums[i] 到 nums[i-1]，则下次比较时 last 的值为 nums[i-1]
                    else
                        last = nums[i-1];
                }
                else
                    return false;
            }
            else {
                // 正常记录 last
                last = nums[i];
            }
        }
        
        return true;
    }
};
```
