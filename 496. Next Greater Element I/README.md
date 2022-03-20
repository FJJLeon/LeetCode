# 496. Next Greater Element I

## 描述

题面：https://leetcode.com/problems/next-greater-element-i/

针对给定的 nums2，对于其中的每个元素，确定在 nums2 后面第一个比它大的值。
nums1 是 nums2 的子集，作为一个查询集合

## 实现

单调栈，可以从前往后也可以从后往前。

``` c++
T = O(N)
S = O(N)

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // 单调栈
        stack<int> st;
        // 数组中数字是唯一的
        unordered_map<int, int> map2;
        // 从前往后遍历，单调栈保存递减序列
        for (int v : nums2) {
            // 若栈顶数top 小于 当前数 v，认为 v 是栈顶数的 next greater
            while (!st.empty() && st.top() < v) {
                map2[st.top()] = v;
                st.pop();
            }
            // 直到栈空，或 top >= v
            st.push(v);
        }
        // 处理 num1 的查询
        vector<int> ans(nums1.size());
        for (int i = 0; i < nums1.size(); i++)
            ans[i] = map2.count(nums1[i]) ? map2[nums1[i]] : -1;
        
        return ans;
    }
};

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> map2;
        // 从后往前遍历，单调栈保存
        for (int i = nums2.size() - 1; i >= 0; i--) {
            int val = nums2[i];
            // 若栈顶数 top 小于 当前数 val，则需要弹出
            while (!st.empty() && st.top() <= val) {
                st.pop();
            }
            // 直到 top > val，认为当前栈顶 top 为当前数 val 的 next greater
            // 若栈空，则说明不存在
            map2[val] = st.empty() ? -1 : st.top();
            st.push(val);
        }
        vector<int> ans(nums1.size());
        for (int i = 0; i < nums1.size(); i++)
            ans[i] = map2[nums1[i]];
        
        return ans;
    }
};
```
可以发现，从后往前遍历可以在某个值为数组最大值的时候确定不存在，而从前往后还需要查询 map
