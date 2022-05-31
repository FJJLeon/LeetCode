# 1461. Check If a String Contains All Binary Codes of Size K

## 题目

题面：https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/

问字符串s中是否包含所有长度为 k 的二进制子串。

## 实现

长度为 k 的二进制子串一共有 2^k 种，如长度为 2 的为 [00,01,10,11] 4 种。

暴力做法就是用 s 所有长度为 k 的子串组成一个字符串集合，若集合大小为 2^k 则符合条件。但是这样会创建很多子串，且字符串集合插入较为耗时。由于题设字符串必然是二进制字符串，可以将长度为 k 的子串认为是整数二进制表示，计算对应的整数个数。这 2^k 个二进制数是连续的，可以用 vector 代替 set 计数。

值得注意的是，可以用滑动窗口优化计算过程。已知当前长度为 k 字符串对应的 k 位二进制数 x，对于下一个长度为 k 的字符串，窗口右滑一位，只要去除 x 中的 LeftMost 位，并在末尾新增一个 RightMost 位，题解称之为 滚动哈希([Rolling Hash](https://en.wikipedia.org/wiki/Rolling_hash))。

``` c++
TC=O(N)
SC=O(2^k)

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size(), need = 1 << k;
        if (n < k)
            return false;
        vector<bool> hash(need, false);
        
        int mask = 0, count = 0;
        // 扩展窗口到字符串长度为 k
        for (int i = 0; i < k; i++) {
            mask = (mask << 1) | (s[i] - '0');
        }
        // 处理第一个 k 长字符串窗口
        hash[mask] = true;
        count++;
        // 滑动窗口
        for (int i = k; i < n; i++) {
            // mask = ((mask ^ ((s[i-k] - '0') << (k-1))) << 1) | (s[i] - '0');
            // 去除 leftmost 位，即右起第 k 位
            mask ^= (s[i-k] - '0') << (k-1);
            // 左移 1 位
            mask <<= 1;
            // rightmost 位置为 s[i]
            mask |= (s[i] - '0');
            // 若遇到新的二进制数，计数
            if (!hash[mask]) {
                hash[mask] = true;
                count++;
            }
        }
        
        return count == need;
    }
};
```

滚动哈希的另一种计算方法是，直接左移一位后与 k 个 1 交运算来去除 leftmost 位

滑动窗口的两步for可以合并，但需要在循环中判断长度，不甚喜欢。

``` c++
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size(), need = 1 << k;
        if (n < k)
            return false;
        vector<bool> hash(need, false);
        
        int mask = 0, count = 0, kOnes = need - 1;
        for (int i = 0; i < n; i++) {
            // 左移一位后与 k 个 1 交，再添加 rightmost
            mask = (mask << 1) & kOnes | (s[i] - '0');
            // 需要先判断窗口长度
            if (i >= k - 1 && !hash[mask]) {
                hash[mask] = true;
                count++;
            }
        }
        
        return count == need;
    }
};
```
