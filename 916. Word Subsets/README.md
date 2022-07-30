# 916. Word Subsets

## 题目

题面：https://leetcode.com/problems/word-subsets/

字符串 a 是 字符串 b 的子集，要求 a 中每个字符个数小于等于 b 中对应字符个数。

若 words2 字符串集合中的每个字符串都是 words1 中某个字符串 w1 的子集，认为 w1 是一个通用字符串，返回 words1 的所有通用字符串。

## 实现

最直观的做法，对于 words2 中的每个字符串，求一个对应的哈希表记录字符个数。然后对于 words1 的每个字符串 w1，用哈希表判断 words2 的每个字符串是否是 w1 的子集，若都是则加入通用集合。

``` c++
TC=O(N2*N1)

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        int n2 = words2.size();
        // 求 words2 中每个字符串的个数哈希表
        vector<vector<int>> w2cnts(n2, vector<int>(26, 0));
        for (int i = 0; i < n2; i++) {
            string& w2 = words2[i];
            for (char c : w2) {
                w2cnts[i][c - 'a']++;
            }
        }
        // 求 words1 中每个字符串的个数哈希表，并判断 words2 中的每个字符串是否是 words1 中的某个字符串的子集
        vector<string> res;
        for (string& w1 : words1) {
            if (isAllSubset(w1, w2cnts))
                res.push_back(w1);
        } 
        return res;
    }
    // 判断 words1 中的某个字符串是否是 words2 中所有字符串的子集
    bool isAllSubset(string& w1, vector<vector<int>>& w2cnts) {
        vector<int> w1cnt(26, 0);
        for (char c : w1)
            w1cnt[c - 'a']++;
        for (auto& w2cnt : w2cnts) {
            for (int i = 0; i < 26; i++) {
                if (w1cnt[i] < w2cnt[i])
                    return false;
            }
        }
        return true;
    }
};
```

然而这样是超时的。稍加思索，若 words2 的每个字符串都是某个字符串的子集，其实该字符串的每个字符需要大于 words2 每个字符串对应字符的最大个数，因此只要把 words2 的哈希表取各字符最大值，作为判断条件。

``` c++
TC=O(N2+N1)

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        int n2 = words2.size();
        // 求 words2 的哈希表中各字符数最大值
        vector<int> w2cnt(26, 0), combine(26, 0);
        for (string& w2 : words2) {
            std::fill(w2cnt.begin(), w2cnt.end(), 0);
            for (char c : w2) {
                combine[c - 'a'] = max(combine[c - 'a'], ++w2cnt[c - 'a']);
            }
        }
        // 求 words1 中每个字符串 w1 的个数哈希表，并判断 w1 是否是 combine 的子集
        vector<int> w1cnt(26, 0);
        vector<string> res;
        for (string& w1 : words1) {
            std::fill(w1cnt.begin(), w1cnt.end(), 0);
            for (char c : w1)
                w1cnt[c - 'a']++;
            bool flag = true;
            for (int i = 0; i < 26; i++) {
                if (w1cnt[i] < combine[i]) {
                    flag = false; break;
                }
            }
            if (flag)
                res.push_back(w1);
        } 
        return res;
    }
};
```
