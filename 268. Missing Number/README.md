# 268. Missing Number

## 题目

题面：https://leetcode.com/problems/missing-number/

长度为 n 的数组，包含 0 到 n 的数，但缺了一个，找到这个数

## 思路与实现

最直观的就是一个用一个集合维护数组中的数，然后遍历应该有的数，找不到的就是缺的那个，但是需要额外空间。

### 1. 异或

既然知道是这 N+1 个数，数组里有 N 个数，将这 2N+1 个数全部异或，就能得到那个单独的数，便是数组中缺的那个。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            res ^= nums[i] ^ (i + 1);
        }
        return res;
    }
};
```

### 2. 求和

把 N+1 个数求和，减去数组里的 N 个数，多的那个就是数组缺的

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            res += (i + 1) - nums[i];
        }
        return res;
    }
};
```

