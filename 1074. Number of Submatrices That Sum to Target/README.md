# 1074. Number of Submatrices That Sum to Target

## 题目

题面：https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/

和为 Target 的子矩阵的个数，即和为 target 的子数组的个数 [560](../560.%20Subarray%20Sum%20Equals%20K/solution.cpp) 的二维版本。

## 思路与实现

朴素暴力的想法，枚举每个 (x1, y1, x2, y2)，计算子矩阵和 sum2D(x1, y1, x2, y2)，判断是否等于 target，这样时间复杂度就爆升到了 O(M^3*N^3)。一个显然的优化，矩阵预处理得到前缀和，将计算子矩阵和的复杂度降低到 O(1)。

### 1. 子矩阵前缀和

矩阵前缀和即 prefix[i][j] 表示 (0,0, i,j) 矩阵的和，可见 [304题](../304.%20Range%20Sum%20Query%202D%20-%20Immutable/)。

由此即可反向计算得到每个子矩阵的和，如 
$$Sum2D(x1, y1, x2, y2) = prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1]$$


``` c++
TC=O(M^2*N^2)
SC=O(M*N)

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        // 多增加一行和一列，用于避免边界条件判断
        vector<vector<int>> prefix(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }
        int res = 0;
        for (int x1 = 1; x1 <= m; x1++) {
            for (int y1 = 1; y1 <= n; y1++) {
                for (int x2 = x1; x2 <= m; x2++) {
                    for (int y2 = y1; y2 <= n; y2++) {
                        if (target == prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1])
                            res++;
                    }
                }
            }
        }
        return res;
    }
};
```

然而，这个时间复杂度在用 c++ vector 实现下会超时，神奇的是用数组实现就不超时，看来 vector 的开销还是挺可观的。

```c++
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int prefix[m+1][n+1];
        memset(prefix, 0, sizeof(prefix));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }
        int res = 0;
        for (int x1 = 1; x1 <= m; x1++) {
            for (int y1 = 1; y1 <= n; y1++) {
                for (int x2 = x1; x2 <= m; x2++) {
                    for (int y2 = y1; y2 <= n; y2++) {
                        if (target == prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1])
                            res++;
                    }
                }
            }
        }
        return res;
    }
};
```

### 2. 哈希表优化

这个优化与一维版本的思路是相同的，将行和列的枚举分离，在确定好两个行后，只计算两行中间的矩阵，此时对列枚举时可利用哈希表记录出现过的 列前缀和，对后续出现的其他前缀和可以直接查询哈希表得到可行的子矩阵数量。

``` c++
TC=O(M^2*N)
SC=O(M*N)

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> prefix(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }
        
        int res = 0;
        unordered_map<int, int> map;
        // 枚举首行 r1 
        for (int r1 = 1; r1 <= m; r1++) {
            // 枚举尾行 r2，r2 >= r1
            for (int r2 = r1; r2 <= m; r2++) {
                // 在两行中间计算 列前缀和，即压缩每列为一个数，则可使用哈希表优化
                // 每次初始化哈希表
                int curSum;
                map.clear();
                for (int c = 1; c <= n; c++) { // 枚举最右列
                    // 计算子矩阵的前缀和
                    curSum = prefix[r2][c] - prefix[r1-1][c];
                    // 直接等于 target，则直接加 1
                    if (curSum == target)
                        res++;
                    // 若之前的前缀和出现过 curSum - target，则在当前子矩阵中去掉之前那个矩阵，剩余的子矩阵和为 Target
                    auto it = map.find(curSum - target);
                    if (it != map.end())
                        res += it->second;
                    // 更新当前子矩阵的前缀和数量
                    map[curSum]++;
                }
            }
        }
        
        return res;
    }
};
```

### 3. 空间优化

可以发现，其实用 O(MN) 的空间对整个矩阵做预处理没有必要，每次只要在枚举行时使用一个一维数组，在尾行逐步滑动时，更新该一维数组作为列前缀和即可。

另外一个小的实现细节，哈希表可以初始设置 map[0] = 1，使得直接等于 target 的处理与其他情况统一。

``` c++
TC=O(M^2*N)
SC=O(N)

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        
        int res = 0;
        unordered_map<int, int> map;
        int colSum[n];
        // 枚举首行 r1 
        for (int r1 = 0; r1 < m; r1++) {
            // 置零列前缀和
            memset(colSum, 0, sizeof(colSum));
            // 枚举尾行 r2，r2 >= r1
            for (int r2 = r1; r2 < m; r2++) {
                // 在尾行滑动过程中，更新列前缀和
                for (int c = 0; c < n; c++)
                    colSum[c] += matrix[r2][c];
                
                map.clear();
                // 统一 curSum == target 的情况
                map[0] = 1;
                int curSum = 0;
                for (int c = 0; c < n; c++) {
                    curSum += colSum[c];
                    auto it = map.find(curSum - target);
                    if (it != map.end())
                        res += it->second;
                    map[curSum]++;
                }
            }
        }
        
        return res;
    }
};
```

值得注意的是，若 m > n，实际上可以控制首列和尾列，用行滑动的一维前缀和实现，两者融合这样时间复杂度是 O(min(m,n)^2*max(m,n))，对应空间复杂度 O(max(m,n))。
