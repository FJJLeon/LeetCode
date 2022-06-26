# 1423. Maximum Points You Can Obtain from Cards

## 题目

题面：https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/

从给定数组的两端取 k 个数，使得这两头的和最大，返回最大和。

## 思路与实现

### 1. 滑动窗口

转换一个视角，在数组中间选择 len(nums) - k 个数，得到最小和，用总和 - 最小和得到两端的最大和。

数组中间选择时可以使用滑动窗口。

``` c++
TC=o(N)
SC=o(1)

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int r = n - k;
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        if (r == 0)
            return total;
        
        int sum = 0, minSum = INT_MAX;
        for (int i = 0, j = 0; j < n; j++) {
            // 窗口向右扩展
            sum += cardPoints[j];
            // 若窗口已经扩展到 k 个数，则更新最小和，然后去除最左边的数
            if (j - i + 1 == r) {
                // 更新最小和
                minSum = min(minSum, sum);
                // 去除最左边的数
                sum -= cardPoints[i++];
            }
        }
        return total - minSum;
    }
};
```

也可以直接考虑两端的数，可供选择的数只能是左侧 k 个数和右侧 k 个数。考虑把两端相连成一个环，也类似一个滑动窗口，先把左侧 k 个加入窗口，向左滑动，迭代更新最大值。

``` c++
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int sum = 0;
        // 左侧 k 个数加入窗口
        for (int i = 0; i < k; i++)
            sum += cardPoints[i];
        int res = sum;
        for (int j = 0; j < k; j++) {
            // 向左滑动，环状滑动到右侧 k 个数
            sum += (cardPoints[n - 1 - j] - cardPoints[k - 1 - j]);
            // 更新最大值
            res = max(res, sum);
        }
        
        return res;
    }
};
```
