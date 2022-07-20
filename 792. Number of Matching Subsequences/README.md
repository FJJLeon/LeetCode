# 792. Number of Matching Subsequences

## 题目

题面: https://leetcode-cn.com/problems/number-of-matching-subsequences/

对于给定单词数组 words，判断是否是字符串 S 的子序列，返回子序列的数量。

## 思路与实现

子序列可以是不连续的，暴力的做法自然是对于每个单词 word，遍历 S 判断是否是子序列，这样每个单词都要进行一次 S 的遍历。

能否减少对 S 的遍历？转换思路，原本是对于每个单词 word 用 S 去判断，现在是对于 S 的每个字符，并行得进行单词判断（每次只能完成部分判断）。

对于每个单词，初始化时根据首字母进行分桶；在遍历到 S 的某个字符 c 时，可以知道 c 所对应的桶中单词已经满足了当前条件（在 S 中匹配到了字符 c），需要进一步判断单词中下一个字符，则将单词重新放入下一个字符所对应的桶中，即前进一位。

实现上，我们不需要每次进行单词切分，只需要在桶中维护单词的索引和下一位期待字符的索引。


``` c++
TC = O(|S| + Σ(|words[i]|))，字符串 S 和每个单词都遍历了一遍
SC = O(|words|)，只保存了索引，桶中只需要单词个数级别的空间

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int wn = words.size();
        // 分桶，对于 words 的每一个 word，根据期望的下一个字符放到对应的桶中
        // key : 当前期望是 'a' + key 的所有 word
        // value：队列，保存 pair - <word 在words 的索引，下一个期望的字符索引（用于下次分桶及判断是否完成匹配）>
        vector<queue<pair<int, int>>> bucket(26);
        // 初始时，每个 word 按照首字符进行分桶
        
        for (int i = 0; i < wn; i++)
            bucket[words[i][0] - 'a'].push({i, 1});
        // 对于 s 中的每个字符，将对应桶所有单词的字符期待前进一位，若匹配完成则更新 res 计数
        int res = 0;
        for (char c : s) {
            // 对应桶的所有单词
            queue<pair<int, int>>& q = bucket[c - 'a'];
            for (int i = q.size(); i > 0; i--) {
                auto [wordIdx, charIdx] = q.front(); q.pop();
                // 匹配完成
                if (charIdx == words[wordIdx].size()) {
                    res++;
                }
                // 字符期待前进一位，重新分桶
                else {
                    bucket[words[wordIdx][charIdx] - 'a'].push({wordIdx, charIdx + 1});
                }
            }
        }
        return res;
    }
};
```
