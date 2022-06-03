# 304. Range Sum Query 2D - Immutable

## 题目

题面：https://leetcode.com/problems/range-sum-query-2d-immutable/

在图像处理中，这是积分图([integral image](https://en.wikipedia.org/wiki/Summed-area_table))的概念。

## 实现

令 **I(x,y)** 代表积分图的第 **x** 行第 **y** 列的值，即：

$$I(x,y)=\sum\limits_{\substack{i<=x \\ j<=y}}matrix(i,j)$$

那么积分图的每个值就是以下公式计算出来的：

$$I(x,y) = I(x-1,y) + I(x,y-1) - I(x-1,y-1) + matrix(x,y)$$

对于体中给定的一个矩阵，已知其左上点 A(r1, c1) 和右下点 D(r2, c2)，可知其右上点B(r2, c1)和左下点C(r1,c2)。矩阵区间和的计算方法如下：

$$Sum(ABCD) = Sum(OD) + Sum(OA) - Sum(OB) - Sum(OC) \\ = I(r2,c2) + I(r1-1,c1-1) - I(r2,c1-1) - I(r1-1,c2)$$

一个小trick是积分图在在左侧和上侧多加了一行和一列，这样就可以避免边界的问题。

``` c++
TC=O(MN)
SC=O(1)

class NumMatrix {
public:
    vector<vector<int>> integra;
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 多加一行和一列，注意后面使用时索引要加1
        integra.resize(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                integra[i][j] = integra[i-1][j] + integra[i][j-1] - integra[i-1][j-1] + matrix[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return integra[row2+1][col2+1] + integra[row1][col1] - integra[row1][col2+1] - integra[row2+1][col1];
    }
};
```
