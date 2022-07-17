# 629. K Inverse Pairs Array

## 题目

题面：https://leetcode-cn.com/problems/k-inverse-pairs-array/

用 1 - n 的数字组成一个数组，其中逆序对的数量为 k 个，问这样的数组有多少个？

## 思路与实现

考虑动态规划，那么怎么操作转移呢？一共就两个可变维度，要么使用 N 个数字，逐步构建从 K - 1 到 K 个逆序对，这就想不到什么明确的转移方法；要么考虑从 N - 1 个数字构建 N 个数字，这里就有说法了，数字是从小到大加入构建的，意味着数字 N 比 1 ~ N - 1 都大，数字 N 插入在第右到左第 P 个位置 （共 N 个位置，包括最右边的位置即不形成新的逆序对），就会形成 P 个新的逆序对，而我们此时已知 N - 1 个数字且逆序对为 K - P 的值，那么就能以此转移到 N 个数字，从而得到动态规划转移过程。

用 dp[i][j] 表示使用 1 ~ i 的数字构建数组，其包含 j 个逆序对的可能方案数量。在求解 dp[i][j] 时，已知 dp[i-1][:] 的状态值。对于 1 ~ i - 1 数字构建的数组，共有 i 个位置可供数字 i 插入，设最右侧位置为 0 号位，则数字 i 插入 p (i-1 >= p >= 0)号位即会形成 p 个新的逆序对，那么使用 dp[i-1][j-p] 的状态值进行转移即可得到同样数量的方案，求和之，即

$$dp[i][j] = \sum_{p=0}^{i-1}dp[i-1][j-p]$$

值得注意的是，在比较前面的计算中可能出现逆序对数量 j 较小，而所用数字 i 较多的情况，即导致了 j-p < 0，逆序对数量是非负的，这样的状态值都是 0。另外，dp[i]][0] = 1，即无逆序对的数组仅为递增排列的数组这一个。

``` c++
TC=O(N^2*K)
SC=O(N*K)

class Solution {
public:
    int kInversePairs(int n, int k) {
        const int mod = 1e9+7;
        vector<vector<int>> dp(n+1, vector<int>(k+1));
        for (int i = 1; i <= n; i++)
            dp[i][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                // 对于 1 到 i-1 数组的每个空位，插空
                for (int p = 0; p < i && p <= j; p++) {
                    dp[i][j] = (dp[i][j] + dp[i-1][j - p]) % mod;
                }
            }
        }
        return dp[n][k];
    }
};
```

然而该做法超时。

进一步优化只能考虑将每一项状态值的计算从 O(N) 降低，在计算 dp[i][j] 时，除了考虑 dp[i-1][:] 还可以考虑 dp[i][j-1]，即使用同样数量的数字，但是少一个的逆序对数量，这样的方案与 dp[i][j] 的计算关系。

$$dp[i][j-1] = \sum_{p=0}^{i-1}dp[i-1][j-1-p]$$

可以发现，dp[i][j] 与 dp[i][j-1] 很多项是重复的，只差了头尾两项，即

$$dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i]$$

由此遍可以在 O(1) 时间计算出每项的值。

``` c++
TC=O(NK)
SC=O(NK)

class Solution {
public:
    int kInversePairs(int n, int k) {
        const int mod = 1e9+7;
        vector<vector<int>> dp(n+1, vector<int>(k+1));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;
            for (int j = 1; j <= min(k, i*(i-1) / 2) ; j++) {
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % mod;
                // dp[i-1][j-i] 不一定存在，注意减法先加一个 Mod
                if (j >= i)
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + mod) % mod;
            }
        }
        return dp[n][k];
    }
};
```

另一个空间优化点是每次转移只需要 i-1 的状态值，因此只需要使用两个数组滚动，优化空间使用。

``` c++
TC=O(NK)
SC=O(K)

class Solution {
public:
    int kInversePairs(int n, int k) {
        const int mod = 1e9+7;
        // 优化空间使用
        vector<int> dp(k+1), tmp(k+1);
        for (int i = 1; i <= n; i++) {
            tmp[0] = 1;
            for (int j = 1; j <= min(k, i*(i-1) / 2) ; j++) {
                // 注意是上一条还是这一条数组
                tmp[j] = (tmp[j-1] + dp[j]) % mod;
                if (j >= i)
                    tmp[j] = (tmp[j] - dp[j-i] + mod) % mod;
            }
            // 滚动数组
            dp.swap(tmp);
        }
        return dp[k];
    }
};
```
