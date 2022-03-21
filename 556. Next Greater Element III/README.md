# 556. Next Greater Element III

## 描述

题面：https://leetcode.com/problems/next-greater-element-iii/

相比系列前两题 (496、503)，本题不是在给定数组中寻找 next greater，而是在数字全排列集合中寻找。


## 实现

这实际上是 [next_permutation](https://en.cppreference.com/w/cpp/algorithm/next_permutation) 的实现，字符串按字典序排序的全排列顺序，找到当前字符串的下一个。

使用 c++ STL [实现](https://leetcode.com/problems/next-greater-element-iii/discuss/101815/C%2B%2B-4-lines-(next_permutation))方便
``` c++
int nextGreaterElement(int n) {
    auto digits = to_string(n);
    next_permutation(begin(digits), end(digits));
    auto res = stoll(digits);
    return (res > INT_MAX || res <= n) ? -1 : res;
}
```

按照 **vector<int>** 来实现

``` c++
T = O(N), N 为 n 的十进制位数
S = O(N)

class Solution {
public:
    int nextGreaterElement(int n) {
        // 生成数位数组 64851 -> [6, 4, 8, 5, 1]
        vector<int> v;
        while (n) {
            v.push_back(n % 10);
            n /= 10;
        }
        reverse(v.begin(), v.end());
        
        // 从后往前找到第一个谷，在 v[i-1]=4, v[i]=8 时停止，谷值为 v[i-1]=4
        int i = v.size() - 1;
        while (i > 0 && v[i - 1] >= v[i]) {
            i--;
        }
        // 若 i 等于 0，则说明数位数组是递减的，不存在 next_permutation
        if (i == 0)
            return -1;
        
        // 从后往前，找到第一个大于（不能等于）谷值的，即 v[j]=5
        int j = v.size() - 1;
        while (v[j] <= v[i - 1])
            j--;
        // 交换谷值与后续第一个大于其的值 [6, 5, 8, 4, 1]
        swap(v[i-1], v[j]);
        // 交换完成后的数位数组已经比原来的大，但不是最接近的
        // 因为新谷值往后的的递减序列本身是最大的排列
        // 逆序之，递增序列则是最小的排列，[6, 5, 1, 4, 8]
        reverse(v.begin() + i, v.end());
        
        // 恢复成数字，利用 long 检查溢出
        // ps. 也可以利用 INT_MAX / 10 和 INT_MAX % 10
        long res = 0;
        for (int i = 0; i < v.size(); i++)
            res = res*10 + v[i];
        
        if (res > INT_MAX)
            return -1;
        else
            return res;
    }
};
```