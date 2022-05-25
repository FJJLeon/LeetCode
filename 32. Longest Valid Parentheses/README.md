# 32. Longest Valid Parentheses

## 题目

题面：https://leetcode.com/problems/longest-valid-parentheses/

给定一个括号字符串，只有小括号，找出最长的合法括号字符串，其中的括号能正确匹配。

## 实现

### 1. 假DP，真暴力，TLE

受[最长回文子串](../647.%20Palindromic%20Substrings/README.md)一题的影响，考虑类似的动态规划方法，令 **dp[l][r]** 代表对应子串 **s[l,r]** 是否是合法括号字符串，那么如何根据子问题进行动态规划呢？

首先，合法字符串一定是偶数长度。其次，要让 s[l,r] 合法，有两种情况：

* s[l+1, r-1] 合法，且 s[l] 和 s[r] 配对
* s[l+1, r-1] 不合法，但是在消除配对括号后，剩余 ")("， 与 s[l]='(' 和 s[r]=')' 分别配对

无论是哪种情况，都要求 **s[i] == '(' && s[j] == ')'**，除此之外，要么 **s[l+1, r-1]** 本就合法，要么 **s[l+1, r-1]** 配对消除后剩余串为 ")("。

因此在动态规划过程中，子串长度由短及长计算。同时，对于不合法子串，保留对应的配对消除后剩余串，用于辅助后续长串的计算。

``` c++
TC=O(N^3)
SC=O(N^3)

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty())
            return 0;
        int n = s.size();
        // dp[l][r] 记录 s[l,r] 是否合法
        bool dp[n][n];
        memset(dp, 0, sizeof(dp));
        // 若 s[l,r] 不合法，reside[l][r] 记录对应的 配对消除后剩余串
        // 如 "((()" -> "(("
        vector<vector<string>> reside(n, vector<string>(n));
        
        int res = 0;
        // i: n-1 -> 0, j: i+1 -> n-1，使得子串长度由短及长计算
        for (int i = n-1; i >= 0; i--) {
            // 子串长只能是偶数
            for (int j = i+1; j < n; j+=2) {
                // 1. 长度为 2 的串
                if (i + 1 == j) {
                    // 1.1 合法
                    if (s[i] == '(' && s[j] == ')') {
                        dp[i][j] = true;
                        res = max(res, 2);
                    }
                    // 1.2 不合法
                    else {
                        dp[i][j] = false;
                        // 不可消除，直接记录剩余串
                        reside[i][j] = s.substr(i, 2);
                    }
                }
                // 2. 长度大于 2
                else {
                    // 2.1. 只有上述讨论的条件合法
                    if (s[i] == '(' && s[j] == ')' && (dp[i+1][j-1] || reside[i+1][j-1] == ")(")) {
                        dp[i][j] = true;
                        res = max(res, j - i + 1);
                    }
                    // 2.2. 不合法
                    else {
                        // 进行消除，如 '(' + ")(((" + ')' -> "(("
                        string tmp = s[i] + reside[i+1][j-1] + s[j];
                        int t = tmp.size();
                        // 右侧可配对
                        if (tmp[t-2] == '(' && tmp[t-1] == ')')
                            tmp = tmp.substr(0, t-2);
                        // 左侧可配对
                        if (tmp[0] == '(' && tmp[1] == ')')
                            tmp = tmp.substr(2);
                        reside[i][j] = tmp;
                    }
                }
            }
        }
        return res;
    }
};
```

按照上面的思路整出来的实现达到了时间空间双O(N^3)，成功出现了 TLE 和 MLE（笑哭）。其实这个做法只是比纯暴力（对于每个子串进行检查）好了一点点，仍旧要检查每个子串，只是对于中心相同的子串的使用了较短串的剩余串来辅助检查。

那么，维护剩余串是必需的吗？并不是。上面分析的两种合法情况实际上是：

* 外括号串呈内外结构，**s[l,r] = (XXXX)**，内部是一个合法子串，左右括号配对，无需剩余串
* 外括号串呈左右结构，**s[l,r] = (XX)ZZ(YY)**，内部是个非法子串，但是内部的某两个括号与左右括号分别配对。在这种情况下，能够在内部找到一个 k，使得 s[l,k] 和 s[k+1,r] 是合法子串。注意，即使与外部左右括号配对的两个内部括号不连续，即 **ZZ** 不为空，此时 **ZZ** 也必然是合法子串。这样计算也无需剩余串。

``` c++
TC=O(N^3)
SC=O(N^2)

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty())
            return 0;
        int n = s.size();
        // dp[l][r] 记录 s[l,r] 是否合法
        bool dp[n][n];
        memset(dp, 0, sizeof(dp));
        
        int res = 0;
        for (int i = n-1; i >= 0; i--) {
            for (int j = i+1; j < n; j+=2) {
                // 1. 长度为 2 的串
                if (i + 1 == j) {
                    dp[i][j] = s[i] == '(' && s[j] == ')';
                }
                // 2. 长度大于 2
                else {
                    // 2.1. 内外结构判断
                    if (s[i] == '(' && s[j] == ')' && dp[i+1][j-1])
                        dp[i][j] = true;
                    // 2.2. 左右结构判断
                    else {
                        // 找到第一个 k，使得 s[i,k] 合法
                        int k = i + 1;
                        while (k+1 < j && !dp[i][k]) {
                            k++;
                        }
                        // 若同时 s[k+1, j] 合法，那么 s[i, j] 也合法
                        if (dp[i][k] && dp[k+1][j])
                            dp[i][j] = true;
                    }
                }
                // 合法则尝试更新
                if (dp[i][j])
                    res = max(res, j - i + 1);
            }
        }
        return res;
    }
};
```
好，一顿分析优化似乎很厉害，一看时间复杂度仍旧是 O(N^3)，仍旧 TLE。

从 2.2 的左右结构判断中可以发现，一旦某几个括号（比如左侧括号串）是合法的，那么这几个括号在其他包含这个串的更长的括号串中的匹配情况也是这样的。即在所有合法子串中，每个括号的配对目标只有一个，括号匹配具有专一性。

这一点与回文串有本质区别，回文串题目中的字符在不同的回文子串里对应的配对情况必然不一样。比如 **abbaabba** 中，对于子串 abba，s[0]=a 与 s[3]=a 配对，而对于整串，s[0]=a 与 s[7]=a 配对。

因此用同样的思路做就不合适。

### 2. 栈模拟

根据专一性，实际上只要使用栈，按照判断回文串的做法读入括号进行配对消除，最后栈中剩余的就是不可配对的括号。夹在不可配对括号中间就是合法串，根据这些剩余括号的索引，即可计算合法串长度。

为了保留不可配对括号的索引，栈中实际上维护括号的索引。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int longestValidParentheses(string s) {
        // 维护还未匹配的括号索引
        stack<int> st;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            // 栈非空，栈顶括号top 与当前括号 s[i] 配对，退栈
            if (!st.empty() && (s[st.top()] == '(' && s[i] == ')') )
                st.pop();
            // 反之（有很多情况），全部压栈
            else
                st.push(i);
        }
        // example: 
        // "(()))()()()(()"
        // "||||)||||||(||", ‘|’ 表示可配对消除
        // st=[4,11]
        // 对应的回文串为 s[0,3] s[5,10] s[12,13]，取最长 
        int res = 0;
        int last = n;
        while (!st.empty()) {
            res = max(res, last - st.top() - 1);
            last = st.top();
            st.pop();
        }
        res = max(res, last);
        
        return res;
    }
};
```

实际上可以在栈模拟的同时计算合法子串长度，每次配对成功时更新。（也可以在配对失败时更新，这可能需要根据一个括号串到底是合法子串还是非法子串多来选择）

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        // 栈顶加入一个初始索引 -1，统一栈空时的不同计算逻辑
        st.push(-1);
        int n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            if (st.top() != -1 && (s[st.top()] == '(' && s[i] == ')') ) {
                st.pop();
                // 更新
                res = max(res, i - st.top());
            }
            else {
                st.push(i);
            }
        }
        return res;
    }
};
```

### 3. 真 DP

有了栈模拟的实现，再想DP会发现应该使用一维DP。

**dp[i]** 表示以 i 索引处字符结尾的最长括号串长度，对应合法括号串必须包括 i 处字符。显然，以 '(' 结尾的子串对应 dp 值必为 0，只需要求解 ')' 结尾的子串。

同样，对应于上文提到的左右和内外结构，单个右括号的计算也类似：

* s[i] = ')'，若 s[i-1] = '('，则形成一个 XXXX() 的左右结构合法子串，有 **dp[i] = dp[i-2] + 2**
* s[i] = ')'，若 s[i-1] != '('，则需要去判断是否能形成一个内外结构即如 (XXXX) 的合法子串，其中最后一个X必然需要是右括号。我们已知 dp[i-1] 的值，即以 i-1 结尾的合法子串X的长度。若在XXXX的左侧有一个左括号，那么就能形成内外结构的更长合法子串，更进一步，如果该左括号左侧还有合法子串，那么能形成一个更长的左右结构子串，形如 YYYY(XXXX)，有 **dp[i] = dp[i-1] + 2 + dp[i - dp[i-1] - 2]**

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), res = 0;
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                // 左右结构
                if (s[i-1] == '(') {
                    // 左测潜在合法子串长 + 2
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                }
                // 内外结构
                else if (i - dp[i-1] - 1 >= 0 && s[i - dp[i-1] - 1] == '(') {
                    // 内合法子串长 + 2 + 左侧潜在合法子串长
                    dp[i] = dp[i-1] + 2 + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
                }
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};
```

### 4. 正逆贪心，无需额外空间

在上述栈模拟中会发现，最后留在栈中的不可匹配括号，除了最后一串可能是左括号，其余的都是右括号。每当遇到不可匹配的右括号，其实对于后续串的括号匹配就相当于重新开始。

利用 left 和 right 两个变量记录左右括号的数量，当左右括号数量相等时，说明以当前字符结尾的是合法括号串，计算其长度。为保证这一判断的合法性，在贪心遍历过程中，若右括号数量大于左括号数量，说明出现了不可匹配的右括号，直接归零重新开始。

然鹅，这种做法无法处理左括号一直大于右括号的情况，即 "(((())"，如果用栈模拟会在栈顶遗留一串左括号。为此，处理方法是使用相反的判断条件，从右往左逆向贪心一遍。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), res = 0;
        // left 左括号数量，right 右括号数量
        int left = 0, right = 0;
        // 正向遍历
        for (int i = 0; i < n; i++) {
            // 括号数量更新
            if (s[i] == '(')
                left++;
            else
                right++;
            // 左右括号数量相等，计算更新
            if (left == right)
                res = max(res, 2 * left);
            // 右括号多于左括号，遇到不可匹配右括号，归零
            else if (right > left)
                left = right = 0;
        }
        
        left = right = 0;
        // 逆向遍历
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '(')
                left++;
            else
                right++;
            
            if (left == right)
                res = max(res, 2 * left);
            // 左括号多于右括号，遇到不可匹配左括号，归零
            else if (left > right)
                left = right = 0;
        }
        
        return res;
    }
};
```
