# 503. Next Greater Element II

## 描述

题面：https://leetcode.com/problems/next-greater-element-ii/

这是一个系列题目，本题相比 **496. Next Greater Element I** 的区别包括
* 数组是一个循环数组，即认为是头尾相连
* 本题中的数组元素可以重复

## 实现

仍使用单调栈实现，区别在于
* 需要遍历两遍数组
* 单调栈中需要存放元素索引以区分重复元素

``` c++
T = O(N)
S = O(N)

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st; // idx
        int n = nums.size();
        vector<int> res(n, -1);
        // 遍历两遍
        for (int i = 0; i < 2*n; i++) {
            // 用 i % n 取真实索引
            int val = nums[i % n];
            // 单调栈栈顶 top 小于当前值 val，认为 val 为 top 的 nexr greater
            while (!st.empty() && nums[st.top()] < val) {
                res[st.top()] = val;
                st.pop();
            }
            // 真实索引入栈
            st.push(i % n);
        }

        return res;
    }
};
```