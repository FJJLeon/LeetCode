# 303. Range Sum Query - Immutable

## 题目

题面：https://leetcode.com/problems/range-sum-query-immutable/

数组不可变，前缀和即可。

## 实现

前缀和数组多加一个，消除边界处理。

``` c++
class NumArray {
public:
    vector<int> integra;
    NumArray(vector<int>& nums) {
        int n = nums.size();
        integra.resize(n+1);
        for (int i = 1; i <= n; i++) {
            integra[i] = integra[i-1] + nums[i-1];
        }
    }
    
    int sumRange(int left, int right) {
        return integra[right+1] - integra[left];
    }
};
```
