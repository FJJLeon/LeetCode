# 1641. Count Sorted Vowel Strings

## 题目

题面：https://leetcode.com/problems/count-sorted-vowel-strings/

用五个元音字母 aeiou，组成长度为 n 的字符串，要求字符串按字典序有序，各字母可用任意次数，返回可组成字符串个数

## 思路与实现

### 1. 动态规划

我的动态规划是这么想的，在字符串构建从左到右构建过程中，假设前一个字符为 'i'，字符串还有 x 的剩余长度，用 **dp[x, 'i']** 表示这样字符串的可能个数：

**dp[x, 'i'] = dp[x - 1, 'i'] + dp[x - 1, 'o'] + dp[x - 1, 'u']**

即前一个字符为 'i' 'o' 'u' 长度还有 x-1 的字符串可以作为 前一个字符为 'i' 还有 x 的长度的字符串除首字符外的部分。

注意到 **dp[x - 1, 'o'] + dp[x - 1, 'u'] = dp[x, 'o']**，因此转移方程 **dp[x, 'i'] = dp[x - 1, 'i'] + dp[x, 'o']**。

``` c++
TC=O(5N)
SC=O(5N)

class Solution {
public:
    int countVowelStrings(int n) {
        vector<map<char, int>> dp(n + 1, map<char, int>());
        // 剩余长度为 1 时
        dp[1]['u'] = 1; // 前一个字符为 'u'，只能填 'u'
        dp[1]['o'] = 2; // 前一个字符为 'o'，能填 'o' 'u'
        dp[1]['i'] = 3;
        dp[1]['e'] = 4;
        dp[1]['a'] = 5; // 前一个字符为 'a'，能填 'a' 'e' 'i' 'o' 'u'
        // 剩余长度为 2 - n
        for (int i = 2; i < n + 1; i++) {
            // 见转移方程解释
            dp[i]['u'] = dp[i-1]['u'];
            dp[i]['o'] = dp[i-1]['o'] + dp[i]['u'];
            dp[i]['i'] = dp[i-1]['i'] + dp[i]['o'];
            dp[i]['e'] = dp[i-1]['e'] + dp[i]['i'];
            dp[i]['a'] = dp[i-1]['a'] + dp[i]['e'];
        }
        // 返回剩余长度为 n，前一个字符为 'a' 的字符串个数
        return dp[n]['a'];
    }
};

当然也可以不用 map，简单做一个字符到数字的映射
class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));
        dp[1][4] = 1;
        dp[1][3] = 2;
        dp[1][2] = 3;
        dp[1][1] = 4;
        dp[1][0] = 5;
        for (int i = 2; i < n + 1; i++) {
            dp[i][4] = dp[i-1][4];
            for (int j = 3; j >= 0; j--) {
                dp[i][j] = dp[i-1][j] + dp[i][j+1];
            }
        }
        return dp[n][0];
    }
};
```

在看了讨论后发现上面我自己动态规划的方法着实是不好理解。

比较好理解的方法是，**dp[n][k]** 代表使用后 k 个元音字符能组成长度为 n 字符串的个数，即 k = 3，只使用 i o u。转移方程：**dp[n][k] = dp[n][k-1]+dp[n-1][k]**，同时认为长度为0的个数为 1。

``` c++
TC=O(5N)
SC=O(5N)

class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(5 + 1));
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= 5; ++k)
                dp[i][k] = dp[i][k - 1] + (i > 1 ? dp[i - 1][k] : 1);
        return dp[n][5];
    }
};
```

进一步，可以只用一维数组

``` c++
TC=O(5N)
SC=O(N)
class Solution {
public:
    int countVowelStrings(int n) {
        vector<int> dp = {0,1,1,1,1,1};
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= 5; ++k)
                dp[k] += dp[k - 1];
        return dp[5];
    }
};
```

### 2. 插空法

元音 aeiou 只能按顺序放入，且可以不放。

转换成插空法，在 N+4 长的字符串中，放入4个隔板，形成五段间隔，在间隔中从左到右放入元音字符即可。这样工有 $n+4 \choose 4$ = $\frac{(n+4)!}{n!4!}$ 种放法。

``` c++
TC=O(1)
SC=O(1)
class Solution {
public:
    int countVowelStrings(int n) {
        return (n+1)*(n+2)*(n+3)*(n+4)/24;
    }
};
```