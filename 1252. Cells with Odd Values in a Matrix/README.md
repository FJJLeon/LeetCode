# 1252. Cells with Odd Values in a Matrix

## 题目

题面：https://leetcode-cn.com/problems/cells-with-odd-values-in-a-matrix/

indices 数组为 [r, c] 形式，对于每个 [r, c]，将 r 行 c 列的值加 1 都自增 1，问完成操作后，矩阵中奇数值单元格的数目。

## 思路与实现

### 1. 朴素模拟

最直接的，建立 mxn 矩阵进行模拟，最后计数即可。

可以想象

``` c++
TC=O(l(m+n) + (m*n))
SC=O(m*n)
```

### 2. 空间优化的模拟

其实模拟过程不需要使用 mxn 矩阵，每次对同一行和同一列的操作是一致的，只要使用两个数组分别表示行和列别自增的次数，对于每个单元格 [x,y]，其值就是所在行和列的自增次数之和。

``` c++
TC=O(l + m*n)
SC=O(m+n)

class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<int> rows(m), cols(n);
        for (auto & idx : indices) {
            int r = idx[0], c = idx[1];
            rows[r]++;
            cols[c]++;
        }
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((rows[i] + cols[j]) & 1) {
                    res++;
                }
            }
        }
        return res;
    }
};
```

### 3. 计数

其实最后对矩阵每个单元格进行判断是不需要的，单元格值为奇数的情况只发生在**所在行和列自增次数的奇偶性不同**时，即单元格所在行自增奇数次同时列自增偶数次，或者行自增偶数次同时列自增奇数次。

因此，只要统计行和列中自增次数为奇数的个数，直接计算即可。我们只关心行列自增次数的奇偶性，而不关系其具体的值，因此可以使用布尔值代替。（好吧，使用 vector<bool> 是不好的实践）

``` c++

class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<bool> rows(m), cols(n);
        // a - 行自增次数为奇数的个数, b - 列自增次数为奇数的个数
        int a = 0, b = 0;
        for (auto& idx : indices) {
            int r = idx[0], c = idx[1];
            a += (rows[r] = !rows[r]) ? 1 : -1;
            b += (cols[c] = !cols[c]) ? 1 : -1;
        }
        // 行奇 * 列偶 + 行偶 * 列奇
        return a * (n - b) + (m - a) * b;
    }
};
```