# 20. Valid Parentheses

## 题目

题面：https://leetcode.com/problems/valid-parentheses/

一个字符串包括三种小中大三种括号，判断是否合法，即括号是否都能按顺序正确匹配。

## 实现

### 栈

用一个栈从左到右压栈，匹配成功一对括号就退栈，最后如果栈空就是合法的，否则非法。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            // 1. 左括号，压栈
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            }
            // 2. 右括号，需要进行匹配
            else {
                // 2.1. 栈空，无法匹配，非法
                if (st.empty()) {
                    return false;
                }
                // 2.2. 栈非空，去栈顶元素进行比较
                char t = st.top();
                // 2.2.1. 能匹配，退栈
                if ((t == '(' && c == ')') || (t == '{' && c == '}') || (t == '[' && c == ']')) {
                    st.pop();
                }
                // 2.2.2 不能匹配，非法
                else {
                    return false;
                }
            }
        }
        // 读完所有括号后栈空，则合法
        return st.empty();
    }
};
```
