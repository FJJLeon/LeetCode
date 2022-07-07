# 97. Interleaving String

## 题目

题面：https://leetcode-cn.com/problems/interleaving-string/

把字符串 s1 和 s2 从头开始的子串交替拼接，问是否能形成字符串 s3

注意，子串是连续字符；要能交替拼接，故两个字符串被分成的子串数量差最大为 1

## 思路与实现

根据题设的描述，我们会把过程认为是首先把 s1 和 s2 切分成数量差小于等于1 的子串序列，然后判断这些子串交替拼接能否形成 s3，这样一个搜索问题显然是指数时间复杂度的。

但我们可以转换这个任务过程的说法，对于两个字符串，我们从某个字符串的开头开始，选择一个能匹配 s3 的字符（或子串），直到这个字符串不能再匹配则选择另一个字符串，直到匹配完成或两个字符串都不能匹配。

这个过程天然保证了输入字符串的切分数量差小于等于 1，且更重要的是这个过程描述更易发现其最优子结构，即使用 **s1[0:i) 和 s2[0:j) 能否形成 s3[0:i+j)，注意左闭右开**，因此问题可以使用动态规划解决。

### 1. 2D DP

其实，我初次实现时认为的最优子结构还包括另一部分，除了能否使用 s1[0:i) 和 s2[0:j) 形成 s3[0:i+j)，还可以在能形成时知道 s1 和 s2 的切分数量差情况。使用一个整型二维数组 **dp[N1+1][N2+1]** 表示动态规划数组，其有两类取值，一类（INT_MAX）是不能形成，另一类（1,0,-1）是能形成时的 s1 和 s2 的切分数量差（|n - m|）。

对于 dp[i][j] 的计算，有两种可能的转移：

* abs(dp[i-1][j]) <= 1，即 s1[0:i-1) 和 s2 [0:j) 可以形成 s3[0:i+j-1)，同时有 s1[i-1] == s3[i+j-1]，那么 s1[0:i) 和 s2 [0:j) 可以形成 s3[0:i+j), dp[i][j] = min(1, dp[i-1][j] + 1), 这个的意思是这一步使用的是 s1 的字符，若之前的末尾是使用 s2 的字符，那么需要切分数量差需要加 1;
* abs(dp[i][j-1]) <= 1，即 s1[0:i) 和 s2 [0:j-1) 可以形成 s3[0:i+j-1)，同时有 s2[j-1] == s3[i+j-1]，那么 s1[0:i) 和 s2 [0:j) 可以形成 s3[0:i+j)，dp[i][j] = max(-1, dp[i][j-1] - 1)，类上.

另外，dp[0][0] 平凡得认为是能形成，为 0；还需要注意第一行和第一列即某个字符串为空时的边界处理。

``` c++
TC=O(N1 * N2)
SC=O(N1 * N2)

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3)
            return false;
        // s1[0:i) 与 s2[0:j) 能否形成 s3[0:i+j)
        // 能形成记录 |n - m|
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, INT_MAX));
        // "" 和 "" 形成 "" 可行
        dp[0][0] = 0;
        // 首列，s1 与 "" 形成 s3
        for (int i = 1; i <= n1; i++) {
            if (abs(dp[i-1][0]) <= 1 && s1[i-1] == s3[i-1])
                dp[i][0] = 1;
        }
        // 首行，"" 与 s2 形成 s3
        for (int j = 1; j <= n2; j++) {
            if (abs(dp[0][j-1]) <= 1 && s2[j-1] == s3[j-1])
                dp[0][j] = -1;
        }
        // s1 与 s2 形成 s3
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (abs(dp[i-1][j]) <= 1 && s1[i-1] == s3[i+j-1]) {
                    dp[i][j] = min(1, dp[i-1][j] + 1);
                }
                else if (abs(dp[i][j-1]) <= 1 && s2[j-1] == s3[i+j-1]) {
                    dp[i][j] = max(-1, dp[i][j-1] - 1);
                }
            }
        }
        return abs(dp[n1][n2]) <= 1;
    }
};
```

然而，会发现记录的切分数量差完全没有作用，这一过程天然保持了数量差小于等于 1，我们只要记录能否形成即可。

``` c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3)
            return false;
        // s1[0:i) 与 s2[0:j) 能否形成 s3[0:i+j)
        // 只记录能否形成
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        
        dp[0][0] = true;
        for (int i = 1; i <= n1; i++) {
            if (dp[i-1][0] && s1[i-1] == s3[i-1])
                dp[i][0] = true;
            // 对于首行和首列，可以提前 break。
            // 但是其他部分不行，s3 子串的可行拼接方法不一定只有一个
            else
                break;
        }
        for (int j = 1; j <= n2; j++) {
            if (dp[0][j-1] && s2[j-1] == s3[j-1])
                dp[0][j] = true;
            else
                break;
        }
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }

        return dp[n1][n2];
    }
};
```

当然上述3个for的写法也可以合并成一个。但是对 i 和 j 同时 if-else 判断代码丑陋，看到中文站题解的分立 if 写法很优雅。

``` c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3)
            return false;
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

        dp[0][0] = true;
        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (i > 0)
                    dp[i][j] = dp[i][j] || (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
                if (j > 0)
                    dp[i][j] = dp[i][j] || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        return dp[n1][n2];
    }
};
```

### 空间优化，1D DP

显然，上述二维 DP 数组在计算过程中实际上只需要前面的一行，可以使用滚动数组进行空间优化。

``` c++
TC=O(N1 * N2)
SC=O(min(N1, N2))

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 < n2)
            return isInterleave(s2, s1, s3);
        if (n1 + n2 != n3)
            return false;
        
        vector<bool> dp(n2 + 1, false);
        
        dp[0] = true;
        
        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (i > 0)
                    dp[j] = dp[j] && s1[i-1] == s3[i+j-1]; // 原本是 dp[j] = dp[j] || (dp[j] && s1[i-1] == s3[i+j-1])，简化了
                if (j > 0)
                    dp[j] = dp[j] || (dp[j-1] && s2[j-1] == s3[i+j-1]);
            }
        }

        return dp[n2];
    }
};
```
