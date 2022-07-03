# 376. Wiggle Subsequence

## 题目

题面：https://leetcode.com/problems/wiggle-subsequence/

找到最长的摆动子序列，摆动子序列就是任意相邻两对数的增减性不同，要么上下上下，要么下上下上。

## 实现

### 1. 动态规划

关键在怎么想到这个动态规划，其实从上面说的来看，一共就两种情况，要么上下要么下上。维护两个一位数组 **pos[i]** （nums[0:i]中以上升数对结尾的最长摆动子序列长度）和 **neg[i]** （nums[0:i]中以下降数对结尾的最长摆动子序列长度）。对于下一个数对：

* 若 nums[i+1] > nums[i]，即下一个是上升数对，那么前面只能是以下降对结尾的摆动子序列才能凭借此上升对得以增长，而前面的以上升对结尾的无法凭此数对增长，只能维持原长度；
* 若 nums[i+1] < nums[i]，与上述相反；
* 若 nums[i+1] == nums[i]，两种摆动序列都无法凭借此数对增长。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> pos(n), neg(n);
        pos[0] = neg[0] = 1;
        for (int i = 1; i < n; i++) {
            int diff = nums[i] - nums[i-1];
            // nums[i+1] > nums[i]
            if (diff > 0) {
                // 以下降对结尾的摆动子序列能凭借此上升对得以增长
                pos[i] = neg[i-1] + 1;
                // 以上升对结尾的无法凭此数对增长，只能维持原长度
                neg[i] = neg[i-1];
            }
            // nums[i+1] < nums[i]
            else if (diff < 0) {
                pos[i] = pos[i-1];
                neg[i] = pos[i-1] + 1;
            }
            // nums[i+1] == nums[i]，两种摆动序列都无法凭借此数对增长
            else {
                pos[i] = pos[i-1];
                neg[i] = neg[i-1];
            }
        }
        // 取较大者作为结果
        return max(pos[n-1], neg[n-1]);
    }
};
```

可以发现，DP 过程中，每次只需要两个数组中的前一个元素，可以优化空间。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        int pos = 1, neg = 1; 
        for (int i = 1; i < n; i++) {
            int diff = nums[i] - nums[i-1];
            if (diff > 0) {
                // 以下降对结尾的摆动子序列能凭借此上升对得以增长
                pos = neg + 1;
            }
            else if (diff < 0) {
                // 以上升对结尾的摆动子序列能凭借此下降对得以增长
                neg = pos + 1;
            }
        }
        
        return max(pos, neg);
    }
};
```


### 2. 贪心

不用动态规划，从如何获取这个最长的摆动子序列角度思考，我们如果遇到连续的上升数对，应该选取哪个放到序列中才能使得总的摆动序列更长，贪心得想必然是选择最后一个（即上升最多的 峰 位置）才能让后续的数对是下降的。

从贪心的角度考虑，我们实际上是在计算**山峰和山谷的数量和**。

注意头尾平凡得认为是山峰和山谷，以及注意数对相等的情况。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return n;
        int prevDiff = nums[1] - nums[0];
        // 若相等，只能选取一个加入摆动序列
        int count = (prevDiff == 0) ? 1 : 2;
        for (int i = 2; i < n; i++) {
            int curDiff = nums[i] - nums[i-1];
            // 遇到山峰或者山谷时，增加摆动序列的长度
            // 注意当前数对若相等，则无需考虑
            if ((curDiff < 0 && prevDiff >= 0) || (curDiff > 0 && prevDiff <= 0)) {
                count++;
                prevDiff = curDiff;
            }
        }
        return count;
    }
};
```