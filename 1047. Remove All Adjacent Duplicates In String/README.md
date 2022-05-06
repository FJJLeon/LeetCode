# 1047. Remove All Adjacent Duplicates In String

## 题目

题面：https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/

类似于消消乐，双消，两个相同字符可以消除，被消除的前后部分再合并进行下一步可能的消除

## 思路与实现

用递归或者迭代的方式不断重复消除+合并字符串的操作可以暴力完成。

双消的顺序不影响最终结果，可以用类似栈的方式从左到右模拟这一过程。

### 1. 字符串栈模拟

把字符串当成栈来模拟双消过程

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    string removeDuplicates(string s) {
        string res = "";
        for (char c : s) {
            // 栈空 或 当前字符不等于栈顶字符，则压栈
            if (res.empty() || res.back() != c) {
                res.push_back(c);
            }
            // 栈非空，且当前字符等于栈顶元素，满足双消条件，出栈
            else {
                res.pop_back();
            }
        }
        return res;
    }
};
```

### 2. 双指针模拟

在原字符串前部，用一个索引移动当成栈来模拟

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    string removeDuplicates(string s) {
        // [0, slot] 作为模拟栈
        int slot = 0, n = s.size();
        // 这里保证了 i >= slot
        for (int i = 0; i < n; i++, slot++) {
            // 入栈
            s[slot] = s[i];
            // 发现栈顶两个字符相等，退两格双消
            if (slot > 0 && s[slot] == s[slot - 1]) {
                slot -= 2;
            }
        }
        // 返回模拟栈中字符串
        return s.substr(0, slot);
    }
};
```