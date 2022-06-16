# 5. Longest Palindromic Substring

## 题目

题面：https://leetcode-cn.com/problems/longest-palindromic-substring/

最长回文子串

## 实现

### 1. 马拉车

上来直接马拉车 O(N) 算法，梭哈再见。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    string longestPalindrome(string s) {
        // 针奇偶长度的回文串进行预处理
        // 如：aba => @a#b#a#$
        // 头尾不同的字符有利于边界判断
        string t = "@";
        for (char c : s)
            t.append(1, c).append(1, '#');
        t.append(1, '$');
        
        // 新串长度
        int n = t.size(), mirror, r;

        // 马拉车核心，已计算过的回文串中右端中
        // 右端最短的那个回文串的 中心 和 右端 位置
        int center = 1, right = 1;
        // 维护新串中，以 i 为中心的回文串半径
        vector<int> radius(n);
        
        // 维护最长回文串及对应半径
        int maxR = -1;
        string res;
        
        for (int i = 1; i < n-1; i++) {
            // 取镜像点
            mirror = 2 * center - i;
            // 当前点的半径最少为 镜像点半径、right - i 中较小的那个
            r = min(radius[mirror], right - i);
            // 尝试中心扩展
            while (t[i - r - 1] == t[i + r + 1])
                r++;
            // 更新半径
            radius[i] = r;
            // 若右端更新，更新 center 和 right
            if (i + r > right) {
                right = i + r;
                center = i;
            }
            // 若新串长度更长，更新最长回文串
            if (r > maxR) {
                maxR = r;
                res = t.substr(i - r, 2 * r + 1);
            }
        }
        // 删除 #
        res.erase(remove(res.begin(), res.end(), '#'), res.end());
        return res;
    }
};
```
