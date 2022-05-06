# 1209. Remove All Adjacent Duplicates in String II

## 题目

题面：https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/

[1047](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/) 题的扩展，由双消变成 K 消。

## 思路与实现

同样的思路，用类似栈的方式从左到右模拟 K 消过程。

### 1. 栈模拟

不同于双消，K 消除需要多个连续字符才能消除，这样需要在栈中维护相同字符的个数 （总不能是在每次检查栈顶是否有K个连续字符）。因此，栈中使用 pair 同时维护栈顶字符和该字符连续个数。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    string removeDuplicates(string s, int k) {
        // 维护栈顶字符和该字符连续个数
        vector<pair<char, int>> st;
        for (char c : s) {
            // 栈空，或 当前字符不等于栈顶字符，则压栈
            if (st.empty() || c != st.back().first) {
                st.push_back({c, 1});
            }
            // 栈非空
            else {
                // 栈顶字符连续个数自增 1
                st.back().second++;
                // 栈顶字符连续个数等于 K，满足 K 消条件，出栈
                if (st.back().second == k) {
                    st.pop_back();
                }
            }
        }
        
        string res = "";
        // 用 vector 模拟栈，此时可以正向遍历构建结果
        for (const auto [c, n] : st) {
            res.append(n, c);
        }
        return res;
    }
};
```

### 2. 双指针模拟

在原字符串前部，用一个索引移动当成栈来模拟。其实这个做法确实是每次检查栈顶是否有K个连续字符，但是使用了额外一个计数数组来加速，所以没有消除栈模拟的空间。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    string removeDuplicates(string s, int k) {
        // [0, slot] 作为模拟栈
        int slot = 0, n = s.size();
        // count[i] 记录 s[i] 字符的连续个数
        vector<int> count(n, 0);
        for (int i = 0; i < n; i++, slot++) {
            // 入栈
            s[slot] = s[i];
            // 栈顶字符相同，栈顶字符计数累计
            if (slot > 0 && s[slot] == s[slot - 1]) {
                count[slot] = count[slot - 1] + 1;
            }
            // 栈顶字符不同，栈顶字符重新计数
            else {
                count[slot] = 1;
            }
            // 栈顶字符计数 达到 K，满足 K 消条件，回退 K 格
            if (count[slot] == k) {
                slot -= k;
            }
        }
        // 返回模拟栈中字符串
        return s.substr(0, slot);
    }
};
```
