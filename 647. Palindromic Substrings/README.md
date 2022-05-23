# 647. Palindromic Substrings

## 题目

题面：https://leetcode.com/problems/palindromic-substrings/

给一个字符串，返回其中所有回文子串的个数。子串是连续的，单个字符也算回文子串。

## 思路与实现

暴力做法就是得到所有的子串 O(N^2)，每个子串判断是否回文O(N)，这样合计的时间复杂度为O(N^3)。

一个优化方法是用已判断过的回文来帮助判断，即动态规划的思想。

具体得说， **s[i,j]** 是一个回文串当且仅当 **s[i+1, j-1]** 是回文串且 **s[i] == s[j]**。

### 1. 动态规划

创建 N*N 二维布尔数组， **dp[l][r]** 代表对应子串 **s[l,r]** 是否是回文串。因此，转移方程为

**dp[l][r] = (s[l] == s[r]) ? dp[l+1][r-1] : false**

值得注意的是，计算顺序有一定要求，需要子串中心在右边的先算，子串长度短的先算，这样才能使规划过程子问题都已经解决。

``` c++
TC=O(N^2)
SC=O(N^2)

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        // 回文子串个数
        int count = 0;
        // l : n-1 -> 0
        for (int l = n - 1; l >= 0; l--) {
            // r : l -> n-1
            for (int r = l; r < n; r++) {
                // 单字符子串
                if (l == r)
                    dp[l][r] = true;
                // 双字符子串，只要判断两个字符是否相等
                else if (l + 1 == r)
                    dp[l][r] = s[l] == s[r];
                // 多字符子串，利用之前的计算结果
                else
                    dp[l][r] = (s[l] == s[r]) ? dp[l+1][r-1] : false;
                
                if (dp[l][r])
                    count++;
            }
        }
        return count;
    }
};
```

### 2. 中心扩展

从动态规划计算过程中可以发现，其实每次动态规划使用的子问题字符串和当前字符串有一个共同的中心。对于奇数长度串，如"XYX"，中心为中间的字符，这里是'Y'；对于偶数长度子串如"XYYX"，中心是中间两个字符的间隙即"YY"的中间。对于长度为 **N** 的字符串，这样的中心一共有 **2N-1** 个

对于每个这样的中心，我们只要不断向两边扩展，直到不再满足回文条件，那么这个中心能形成的回文串就全部计算完毕。

以这 **2N-1** 个中心索引进行遍历，用左右两个指针从中心向外扩展。这实际上是把中心相同的子串放到一起进行判断，相比动态规划可以提前停止不必要的计算。

``` c++
TC=O(N^2)
SC=O(1)

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int count = 0;
        // 对于每个中心
        for (int c = 0; c < 2*n-1; c++) {
            // 计算左右字符指针索引，可以统一奇偶长度子串
            // 初始时对于奇长度子串（中心索引为偶） l == r
            // 对于偶长度子串（中心索引为奇） l + 1 == r
            int l = c / 2, r = (c+1) / 2;
            // 中心扩展
            while (l >= 0 && r < n && s[l] == s[r]) {
                l--;
                r++;
            }
            // 计数回文串个数
            // s[l,r] 是以 c 为中心的最长回文串
            // 其内部一共有 (r-l)/2 个子回文串
            count += (r - l) / 2;
        }
        
        return count;
    }
};
```

另一种实现方法是以每个字符为中心，但是由于奇偶子串的不同，需要进行两次中心扩展，一次以 **l=c,r=c**，另一次以 **l=c,r=c+1**。

``` c++
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int count = 0;
        // 对每个字符为中心
        for (int c = 0; c < n; c++) {
            // 两次中心扩展
            for (int ode = 0; ode <= 1; ode++) {
                int l = c, r = c + ode;
                while (l >= 0 && r < n && s[l] == s[r]) {
                    l--;
                    r++;
                }
                count += (r - l) / 2;
            }
        }
        
        return count;
    }
};
```

### 3. Manacher's Algorithm 马拉车算法

从中心扩展进一步优化而来，实现了线性时间复杂度。

第一步，统一了奇偶长度子串，使得后续操作一致。做法是在原串**S**的每两个字符中间插入一个新字符，这样形成新串**T**，T的每个字符正好对应了原串 **2|S|-1** 个中心。

第二步，在计算过程中记录每个中心 i 能扩展得到的最长回文串半径 **radius[i]**，利用回文串的对称性进一步帮助后续计算。

具体来说，我们已知一个已计算完成的结果，索引位置 **center** 处的最长回文串半径为 **radius[center]**（后记为Rc），即 **T[C - Rc, C + Rc]** 是一个回文串，记 right = C + Rc。

现在要计算索引 **i, (i>center)** 处的最长回文半径，

* 若 i < right，可以得到一个 i 关于 center 的对称点 **mirror = center - (i - center)**， mirror 已经计算过，此处最长回文串半径为 **radius[mirror]**（后记为 Rm）。由于 mirror 和 i 关于 Center 中心对称，且都在回文串中。因此，以 i 为中心和以 mirror 为中心的最长回文串半径可以相等。但是这要求该半径下，以 i 为中心的回文串右边界不超过 right，即 **i + Rm <= center + Rc = right**，超过部分不能利用对称性保证回文，仍需要使用中心扩展进行计算。
* 若 i >= right，则需要中心扩展计算。

另一个问题是如何选取这个 **center**，我们需要尽可能复用之前的结果，因此，我们在计算过程中不断维护更新右边界即 right 最靠右的那个 center 中心。

``` c++
TC=O(N)，right 只会线性更新到 N，便可复用计算所有半径
SC=O(N)

class Solution {
public:
    int countSubstrings(string s) {
        // aaa -> ^#a#a#a#$
        // ^ 和 $ 开头结尾有利于中心扩展时的消除边界判断
        string t = "^#";
        for (char c : s)
            t.append(1, c).append(1, '#');
        t.append(1, '$');
        
        int n = t.size();
        int count = 0;
        // 记录每个中心能扩展得到的最长回文串半径
        vector<int> radius(n, 0);
        // 维护右边界最远的中心扩展结果，center 为该子回文串中心，right 为右边界
        int center = 0, right = 0;
        for (int i = 1; i < n - 1; i++) {
            // 得到关于 center的中心对称点
            int mirror = 2 * center - i;
            // i 的计算可复用前面的结果，为 right-i 和 radius[mirror] 中较小的那个
            if (i < right)
                radius[i] = min(right - i, radius[mirror]);
            // 继续中心扩展，利用了T构建时的 ^ 和 $，无需边界判断
            while (t[i - radius[i] - 1] == t[i + radius[i] + 1])
                radius[i]++;
            // 有边界有更远的，更新之
            if (i + radius[i] > right) {
                center = i;
                right = i + radius[i];
            }
            // 计算以 i 为中心的回文子串数量
            count += (radius[i] + 1) / 2;
        }
        
        return count;
    }
};
```

## Reference

* [马拉车算法，其实并不难](https://blog.51cto.com/u_13604316/4157186)