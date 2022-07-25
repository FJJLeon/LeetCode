# 74. Search a 2D Matrix

## 题目

题面：https://leetcode-cn.com/problems/search-a-2d-matrix/

矩阵中每行都是递增的，且每行的开头都比上一行的末尾更大，在矩阵中搜索目标值。

## 实现

这种矩阵实际上是折叠的一维递增序列，可以直接按照一维二分搜索来实现。

``` c++
TC=O(log(m*n))
SC=O(1)

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size(), col = matrix[0].size();
        int l = 0, r = row * col - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int val = matrix[mid/col][mid%col];
            if (val == target)
                return true;
            else if (val < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return false;
    }
};
```
