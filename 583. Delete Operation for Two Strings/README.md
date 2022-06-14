# 583. Delete Operation for Two Strings

## 题目

题面：https://leetcode-cn.com/problems/delete-operation-for-two-strings/

两个字符串，每步可以在某个字符串中删除一个字符，问最少需要多少步，才能使两个字符串相同。

## 实现

编辑距离的弱化，动态规划解之。

### 1. 二维 DP

令 **dp[i][j]** 表示使 word1[0,i) 和 word2[0,j) 相同所需要的最少删除操作，姑且称之为删除距离。注意 word[0,i) 不包括字符 i，即 word[0,0)为空字符串。因此，设 word1 长度为 n1, word2 长度为 n2，则该二维DP数组的大小为 (n1+1) * (n2+1)。

在计算 dp[i][j] 时，针对需要考虑两种情况：

* 如果 word1[i-1] == word2[j-1]，则 dp[i][j] = dp[i-1][j-1]，即 word1[0,i) - word2[0,j) 的删除距离与 word1[0,i-1) - word2[0,j-1) 的删除距离相等；
* 如果 word1[i-1] != word2[j-1]，则 dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1，即选择 word1[0,i-1) - word2[0,j) 和 word1[0,i) - word2[0,j-1) 中较小的删除距离加上删除多余元素的 1 次操作。

从而，转移方程为：

$$dp[i][j] = \begin{cases}
dp[i-1][j-1], &  word1[i-1] = word2[j-1] \\
min(dp[i-1][j], dp[i][j-1]) + 1, &  word1[i-1] \ne word2[j-1]
\end{cases}$$

另外，对于第一行和第一列的边界条件，因为 word1[0,0) 和 word2[0,0) 为空字符串，因此 dp[0][j] = j，dp[i][0] = i。

``` c++
TC=O(MN)
SC=O(MN)

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
        // 第一列和第一行的边界条件
        for (int i = 1; i <= n1; i++)
            dp[i][0] = i;
        for (int j = 1; j <= n2; j++)
            dp[0][j] = j;
        // 转移方程
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j]);
            }
        }
        
        return dp[n1][n2];
    }
};
```

### 2. 一维 DP

可以发现，转移方程中计算 **dp[i][j]** 需要 **dp[i-1][j-1]、dp[i-1][j]、dp[i][j-1]**，即仅需要左、上、左上三个状态，因此可以用一维 DP 来解决。

另外，对于第一行和第一列的边界条件，可以统一为：

$$dp[i][j] = i + j, i = 0 \ \text{or} \ j = 0$$

可以使用两个一维数组来计算，一个用来记录本行状态，一个用来记录上一行状态。也可以用一个仅有两行的二维数组配合行号的奇偶性来计算。

``` c++
TC=O(MN)
SC=O(min{M,N})

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        if (n2 > n1)
            return minDistance(word2, word1);
        // 两个动态规划数组
        vector<int> dp(n2 + 1), tmp(n2 + 1);

        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                // 第一行和第一列的边界条件
                if (i == 0 || j == 0)
                    tmp[j] = i + j;
                // 转移方程，左上 = dp[j-1]
                else if (word1[i-1] == word2[j-1])
                    tmp[j] = dp[j-1];
                // 左 = tmp[j-1], 上 = dp[j]
                else
                    tmp[j] = 1 + min(tmp[j-1], dp[j]);
            }
            // 保存本行状态供下一行使用
            dp.swap(tmp);
        }
        
        return dp[n2];
    }
};
```

实际上，需要保存的只有左上状态，仅需要一个变量维护。

``` c++
TC=O(MN)
SC=O(min{M,N})

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        if (n2 > n1)
            return minDistance(word2, word1);
        vector<int> dp(n2 + 1);
        // last 维护左上状态
        int last, tmp;
        for (int i = 0; i <= n1; i++) {
            // 一行结束，重置 last
            last = 0;
            for (int j = 0; j <= n2; j++) {
                // 暂存 dp[j]，为上一行 j 状态
                tmp = dp[j];
                if (i == 0 || j == 0)
                    dp[j] = i + j;
                // 左上 = last
                else if (word1[i-1] == word2[j-1])
                    dp[j] = last;
                // 左 = dp[j-1], 上 = dp[j]
                else
                    dp[j] = 1 + min(dp[j-1], dp[j]);
                // 维护 last，作为右侧计算时的 左上 状态
                last = tmp;
            }
        }
        
        return dp[n2];
    }
};
```
