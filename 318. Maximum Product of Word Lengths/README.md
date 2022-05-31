# 318. Maximum Product of Word Lengths

## 题目

题面：https://leetcode.com/problems/maximum-product-of-word-lengths/

计算不相交（没有相同字符）的单词长度乘积的最大值

## 实现

对于每个单词，检查其与其他单词是否有相同字符，若没有，则计算长度乘积用于更新最大值。

那么问题主要在于判断两个单词是否有相同字符，显然可以转换成字符集合来计算是否有交集，更好的做法是使用位集。当然，由于这里只有26个小写字母，用一个整数其实就够了。

``` c++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        vector<bitset<26>> bits(n);
        for (int i = 0; i < n; i++) {
            // 计算单词对应的 bitset
            for (char c : words[i])
                bits[i].set(c - 'a');
        }
        
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 若两个单词的 bitset 的交集全为 0，则用长度乘积更新最大值
                if ((bits[i] & bits[j]).none()) {
                    res = max(res, (int)(words[i].size() * words[j].size()));
                }
            }
        }
        return res;
    }
};
```

只用一个整数。

上面的两个循环其实可以合并。

``` c++
TC=O(N^2)
SC=O(N)

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size(), res = 0;
        vector<int> bits(n);
        for (int i = 0; i < n; i++) {
            int mask = 0;
            // 计算单词对应的整数 mask
            for (char c : words[i])
                mask |= 1 << (c - 'a');
            bits[i] = mask;
            // 若 words[i] 与左侧的单词 mask 交的结果为 0，则更新
            for (int j = 0; j < i; j++) {
                if (!(bits[j] & mask))
                    res = max(res, (int)(words[i].size() * words[j].size()));
            }
        }
        
        return res;
    }
};
```
