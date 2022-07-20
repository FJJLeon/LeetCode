# 1260. Shift 2D Grid

## 题目

题面：https://leetcode-cn.com/problems/shift-2d-grid/

一维数组 shift 的二维扩展

## 思路与实现

暴力的做法自然是一次次平移。

### 1. 展平到一维

可以把二维矩阵展平成一维，然后在一维进行 Shift 后转换回二维，进行迁移。当然不需要真的进行展平，只要对坐标进行转换即可。


``` c++
TC=O(M*N)

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size(), mn = m * n;
        vector<vector<int>> res(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int idx = (i * n + j + k) % mn;
                res[idx / n][idx % n] = grid[i][j];
            }
        }
        return res;
    }
};
```

如果不展平，直接考虑行和列坐标也可以，nj = (j + k) % n, ni = (i + (j + k) / n) % m

### 2. 基于 Reverse 的 In-place 实现

一维的shift有一个三次 Reverse 的实现，此处同理

```
reverse[0,n): [0...n-k-1,n-k...n-1] -> [n-1...n-k,n-k-1...0]
reverse[0,k): [n-1...n-k,n-k-1...0] -> [n-k...n-1,n-k-1...0]
reverse[k,n): [n-k...n-1,n-k-1...0] -> [n-k...n-1,0...n-k-1]
```

``` c++
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        m = grid.size(), n = grid[0].size();
        k %= m * n;
        reverse(grid, 0, m * n);
        reverse(grid, 0, k);
        reverse(grid, k, m * n);
        return grid;
    }
private:
    int m, n;
    void reverse(vector<vector<int>>& grid, int start, int end) {
        end--;
        while (start < end) {
            swap(grid[start/n][start%n], grid[end/n][end%n]);
            start++; end--;
        }
    }
};
```