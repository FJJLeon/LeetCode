# 378. Kth Smallest Element in a Sorted Matrix

## 题目

题面：https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/

一个行列分别升序的矩阵，求第K小的元素。

## 思路与实现

行列分别有序的矩阵，势必要用到有序才能有效求解。

### 1. 暴力

使用一个 O(N^2) 的数组，把矩阵中的所有元素都存入数组中，然后排序，得到第 K 小的元素，时间复杂度 O(N^2logN^2) = O(N^2logN)，空间复杂度 O(N^2)。

### 2. 最大堆

用一个最大堆（优先队列）维护最小的 K 个数，依次插入每行的元素，当堆大小超过 K 时，弹出堆顶元素（当前最大值），时间复杂度 O(N^2logK)，空间复杂度 O(K)。

``` c++
TC=O(N^2logK)
SC=O(K)

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 最大堆维护最小的 K 个数
        priority_queue<int> pq;
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                pq.push(matrix[i][j]);
                // 当堆大小超过 K 时，弹出堆顶元素（当前最大值）
                if (pq.size() > k)
                    pq.pop();
            }
        }
        return pq.top();
    }
};
```

### 3. 最小堆，合并N个有序数组

对于 N 个分别有序的行数组，使用最小堆维护每行的指针，每次弹出堆顶元素（最小值），将对应行的下一个元素插入堆中，重复 K 次即可得到全局第 K 小的数。相当于合并 N 个分别有序的数组，但是此处可以在找到第 K 个元素之后，直接返回。此处也可以维护每列的指针，逻辑类似。

优先队列中需要关系到元素值及对应的行列号，从而获取对应行的下一个元素。可以使用 **pair<int, int>(value, r*n+c)**，也可以使用 **array<int, 3>(value, r, c)**, 或者 **pair<int, int>(r, c)**。

``` c++
TC=O(KlogN)
SC=O(N)

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 维护一个最小堆，保存 <value, r*n+c>
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        int n = matrix.size();
        // 把每行的第一个元素插入堆中
        for (int i = 0; i < n; i++) {
            pq.push({matrix[i][0], i * n});
        }
        // 弹出堆顶元素，插入对应行的下一个元素，重复 K 次即可得到全局第 K 小的数
        while (k > 1) {
            auto [_, idx] = pq.top(); pq.pop();
            if ((idx + 1) % n != 0) {
                pq.push({matrix[idx/n][idx%n + 1], idx + 1});
            }
            k--;
        }
        return pq.top().first;
    }
};


class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 效果类似，最小堆只维护行列号，不维护值，用lambda比较函数捕获矩阵进行比较
        auto cmp = [&](const pair<int, int>& c1, const pair<int, int>& c2) {
            return matrix[c1.first][c1.second] > matrix[c2.first][c2.second]; 
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        int n = matrix.size();
        
        for (int j = 0; j < n; j++) {
            pq.push({0, j});
        }
        while (k > 1) {
            auto [i, j] = pq.top(); pq.pop();
            if (i + 1 < n) {
                pq.push({i + 1, j});
            }
            k--;
        }
        return matrix[pq.top().first][pq.top().second];
    }
};
```

### 4. 值域二分搜索 + 马鞍峰搜索

二分搜索一般作用于索引域，但此题我们作用于值域。可以发现，矩阵左上角值是全局最小，而右下角值是全局最大。

对这两个值进行二分搜索，对于每个 mid 值，我们可以使用马鞍峰搜索（类似 [240 题线性解法](../240.%20Search%20a%202D%20Matrix%20II/README.md)）在O(2N)的时间内找到矩阵中小于等于 mid 的数的个数 cnt。

* 若 cnt 小于 k，则说明第 k 小的值在 mid 右边，即大于 mid，将区间二分继续搜索，left = mid + 1；
* 若 cnt 大于等于 k，则说明第 k 小的值不大于 mid，right = mid，不能是 mid - 1。

我们要进行搜索，找到矩阵中第一个使得 cnt 等于 k 的 mid 值。

``` c++
TC=O(Nlog(maxV-minV))，二分搜索需要 log(maxV-minV) 次搜索，每次 O(2N) 计算个数。
SC=O(1)

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        // 对值域进行二分搜索
        int left = matrix[0][0], right = matrix[n-1][n-1];
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cnt = lessOrEqual(matrix, mid);
            // 若 cnt 小于 k，则说明第 k 小的值大于 mid，left = mid + 1
            if (cnt < k) {
                left = mid + 1;
            }
            // 若 cnt 大于等于 k，则说明第 k 小的值不大于 mid，right = mid
            else {
                right = mid;
            }
        }
        return left;
    }
    // 马鞍峰搜索，找到矩阵中小于等于 mid 的数的个数
    int lessOrEqual(const vector<vector<int>>& matrix, const int t) {
        int n = matrix.size();
        int i = 0, j = n - 1, cnt = 0;
        // 从右上角点开始搜索
        while (i < n && j >= 0) {
            // 当前值小于等于 t，当前行左侧都小于等于 t，累加列数，向下移动一行
            if (matrix[i][j] <= t) {
                i++;
                cnt += j + 1;
            }
            // 当前值大于 t，向左（较小方向）移动一列
            else {
                j--;
            }
        }
        return cnt;
    }
};
```

### Reference

1. [值域的二分查找](https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/solution/dui-shu-zhi-er-fen-cha-zhao-by-hyj8/)
