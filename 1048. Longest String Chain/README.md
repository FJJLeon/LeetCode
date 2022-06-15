# 1048. Longest String Chain

## 题目

题面：https://leetcode-cn.com/problems/longest-string-chain/

首先，字符串 a 中插入一个字符变成字符串 b，称 a 为 b 的前缀。

连续的几个字符串按顺序为前缀，称之为 String Chain。

给定一组字符串，问最长的 String Chain 的长度。

## 实现

从图的角度看，认为字符串为图的节点，前缀为有向边，从而转化成一个有向无环图(DAG)，对图进行拓扑遍历即可得到最长的字符串链。

按这个思路，不建图，直接用一个字典记录**以每个字符串结尾的的最长链的长度**，用动态规划的方法逐步更新。

首先将字符串按长度排序，如果从小到大寻找合法的后缀，需要对两个字符串进行比较匹配；但是，如果我们反着看，从较长字符串找可能的前缀较短字符串，则只需要从长字符串删除一个字符，判断剩下的字符串是否存在于字典中即可。相应的，记录的也变成了以**每个字符串开始的反向最长链长度**。

``` c++
TC=O(NlogN + NLL), L 为字符串长度
SC=O(N)

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        // 按字符串长度从大到小排序
        sort(words.begin(), words.end(), [](const string& w1, const string& w2) {return w1.size() > w2.size();});
        // 字典记录以每个字符串结尾的反向最长链（见上）的长度，用动态规划的思路更新
        unordered_map<string, int> lens;
        // 初始为 1
        for (string& w : words) {
            lens[w] = 1;
        }
        // 对每个字符串，从大到小遍历，寻找可能的前缀
        for (string w : words) {
            int n = w.size(), len_n = lens[w];
            // 删除一个字符，判断剩下的字符串是否存在于字典中
            for (int i = 0; i < n; i++) {
                string t = w; t.erase(i, 1);
                auto it = lens.find(t);
                // 若存在，则更新新字符串的长度
                if (it != lens.end()) {
                    it->second = max(it->second, len_n + 1);
                }
            }
        }
        // 求最长链的长度，其实只要计算长度最短的几个字符串值即可
        int res = 0;
        for (auto& [w, l] : lens)
            res = max(res, l);
        
        return res;
    }
};
```
