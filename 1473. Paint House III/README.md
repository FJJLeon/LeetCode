# 1473. Paint House III

## 题目

题面：https://leetcode-cn.com/problems/paint-house-iii/

本题是 Paint House 系列题的第三题，然而前两题是Plus专属，简单描述一下难度进阶：

* 第一题是将 n 个房子刷成三种颜色，相邻的房子不能是相同的颜色，cost[i][j] 表示房子 i 刷成第 j 种颜色的成本，求最小的总成本；
* 第二题是刷成 k 种颜色，其余不变；
* 第三题即本题的难度提升在两个方面条件：
  * 第一，相邻房子不同色的条件提升为需要划分为 target 个街区（连续的同色房）；
  * 第二，存在已经刷成 j 色的房子，不能修改且无需再花费。

## 思路与实现

LeetCode 在每日一题中整了一个三维DP，有点晕。

系列的前两题显然是是二维动态规划（可优化空间），而第三题是三维DP，使用 **dp[i][j][k] 表示将前 i 间房子刷色，且第 i 间房子的颜色编号为 j，前 i 间房子形成的街区数量为 k 的所有可行方案中的最小成本**。

在计算 dp[i][j][k] 过程中需要对房子是否已经涂色进行分类讨论：

* 首先考虑房子没有被涂色的情况，即 houses[i] == 0，房子 i 可以被刷成 1 ~ n 中任意一种颜色（计算某一个状态时该颜色为 j），此时需要根据**房子 i 的颜色 j 与前一个房子即 i - 1 号房子的颜色 p 是否相同** 来判断房子 i 是否会形成一个新的街区，即对于 dp[i][j][k] 的需要从 min(dp[i-1][p][k]), p != j 和 dp[i-1][j][k-1] 中的最小值进行状态转移：

$$
\begin{equation}
dp[i][j][k] = cost[i,j-1] + min
\begin{cases}
min(dp[i-1][p][k]) & p \neq j \\
dp[i-1][j][k-1] & p = j
\end{cases}
\end{equation}
$$

* 然后考虑有房子已经被涂色的情况，即 houses[i] = j0，那么对于 dp[i][j][k] 中 j != j0 的状态都是无意义的，使用一个 INF 值表示。对于 j = j0 的情况，则与上述涂色方式相同。

$$
\begin{equation}
dp[i][j][k] = 
\begin{cases}
min
\begin{cases}
min(dp[i-1][p][k]) & p \neq j \\
dp[i-1][j][k-1] & p = j
\end{cases} 
, & j = houses[i] \\
INF & j \neq houses[i]
\end{cases}
\end{equation}
$$

细节：

* 为避免溢出，无效状态 INF 可使用 INT_MAX / 2 或者 0x3f3f3f3f 进行表示，使用一个有「累加空间」的值作为「正无穷」
* 分区为 k = 0 的状态不存在，初始化为 INF 无效值
* 题设颜色使用了 1~n 表示，将房子和街区编号统一都使用 1-index 的索引，同时可以避免 0 边界值讨论，因此状态数组为 (m+1)\*(n+1)\*(t+1)

``` c++
TC=O(M*N^2*T)
SC=O(M*N*T)
class Solution {
public:    
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        const int INF = 0x3f3f3f3f;
        // dp[i][j][k] 表示前 i 间房子刷色，且第 i 间房子的颜色编号为 j，前 i 间房子形成的街区数量为 k 的所有可行方案中的最小成本
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(target+1)));
        // 分区为 k = 0 的状态不存在
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j][0] = INF;
            }
        }
        
        for (int i = 1; i <= m; i++) {
            int color = houses[i - 1];
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= target; k++) {
                    // 分区数量大于房子数量，不存在可行方案
                    if (k > i) {
                        dp[i][j][k] = INF;
                        continue;
                    }
                    // 房子 i 已经涂色，涂为 color，用 (2) 式计算
                    if (color != 0) {
                        // j = color 才能进行状态转移
                        if (j == color) {
                            int cur = INF;
                            // color 与前一个房子的颜色 p 不相同，形成新的街区
                            for (int p = 1; p <= n; p++) {
                                if (p != j)
                                    cur = min(cur, dp[i-1][p][k-1]);
                            }
                            // color 与前一个房子的颜色 p 相同，不形成新的街区
                            dp[i][j][k] = min(cur, dp[i-1][j][k]);
                        }
                        // j != color 的状态无效
                        else
                            dp[i][j][k] = INF;
                    }
                    // 房子 i 未涂色，需要 cost，用 (1) 式计算
                    else {
                        int cur = INF;
                        // color 与前一个房子的颜色 p 不相同，形成新的街区
                        for (int p = 1; p <= n; p++) {
                            if (p != j)
                                cur = min(cur, dp[i-1][p][k-1]);
                        }
                        // color 与前一个房子的颜色 p 相同，不形成新的街区
                        // 最后加上涂色成本 cost[i-1][j-1]
                        dp[i][j][k] = min(cur, dp[i-1][j][k]) + cost[i - 1][j - 1];
                    }
                }
            }
        }
        // 选取把所有房子涂色，且形成 target 街区的方案中的最小成本
        int res = INF;
        for (int i = 1; i <= n; i++) {
            res = min(res, dp[m][i][target]);
        }
        return res == INF ? -1 : res;
    }
};
```

### 空间优化

注意到，dp[i][j][k] 的状态转移计算只与前一个房子的状态即 dp[i-1][:][:] 有关，可以进行空间优化到 O(N*T)。


### 时间优化

更进一步，在时间复杂度上，类似于系列第二题的做法，只需要记录 dp[i-1][:][k-1] 中的最大值、次大值、以及最大值的索引（用于判断是否能使用最大值）将原本需要 O(N) 搜索降低到 O(1)，从而整体时间复杂度降低到 O(M\*N\*T)。

## Reference

* [【宫水三叶】三维动态规划，以及其「状态定义」由来](https://leetcode.cn/problems/paint-house-iii/solution/gong-shui-san-xie-san-wei-dong-tai-gui-h-ud7m/)
* [粉刷房子 III](https://leetcode.cn/problems/paint-house-iii/solution/fen-shua-fang-zi-iii-by-leetcode-solutio-powb/)

