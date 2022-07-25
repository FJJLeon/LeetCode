# 240. Search a 2D Matrix II

## 题目

题面：https://leetcode-cn.com/problems/search-a-2d-matrix-ii/

矩阵中每行和每列都是单独有序的，在矩阵中搜索目标值。

## 实现

直接暴力搜索是 O(M*N) 时间复杂度，显然不行。

矩阵是部分有序的，显然有更好的做法。对每行或者每列进行单独二分搜索，时间复杂度为 O(MlogN) 或者 O(NlogM)，有一定优化。

但是可以想到还有更好的做法，但是一时间想不到。

### 抽象二叉搜索树

以右上点为根，各条对角线作为子节点，可以发现数值按照 BST 的规则进行排列，左侧都是较小值，右侧都是较大值。因此可以类似BST的搜索来实现，从根节点开始：

比当前节点大，就走右值（下值），实际上保证了左侧的值都比目标小，排除了一行；比当前节点小，就走左值，实际上保证了下侧的值都比目标大，排除了一列。

``` c++
TC=O(M + N)
SC=O(1)

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            int val = matrix[i][j];
            if (val == target)
                return true;
            
            if (val < target)
                i++;
            else
                j--;
        }
        return false;
    }
};
```
很优美。

### 四分归并

对于矩阵中心点，可以发现左上矩阵的值都比中心点小，右下的矩阵值都比中心点大，而右上和左下的则不一定。因此对于每个中心点可以排除 1/4 矩阵，在余下的三个子矩阵中归并搜索。


### Reference

1. [【宫水三叶】一题双解 :「二分」&「抽象 BST」](https://leetcode.cn/problems/search-a-2d-matrix-ii/solution/gong-shui-san-xie-yi-ti-shuang-jie-er-fe-y1ns/)
2. [详细通俗的思路分析，多解法](https://leetcode.cn/problems/search-a-2d-matrix-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-5-4/)
