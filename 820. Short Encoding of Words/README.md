# 820. Short Encoding of Words

## 题目

题面：https://leetcode-cn.com/problems/short-encoding-of-words/

Given a list of words, we may encode it by writing a reference string `S` and a list of indexes `A`.

For example, if the list of words is `["time", "me", "bell"]`, we can write it as `S = "time#bell#"` and `indexes = [0, 2, 5]`.

Then for each index, we will recover the word by reading from the reference string from that index until we reach a `"#"` character.

What is the length of the shortest reference string S possible that encodes the given words?

Example:
```
Input: words = ["time", "me", "bell"]
Output: 10
Explanation: S = "time#bell#" and indexes = [0, 2, 5].

Input: words = ["me", "times"]
Output: 9
Explanation: S = "times#me#" and indexes = [0, 6].
    note each masked word must be suffix of reference word, a.k.a ended at "#"
    and word appears later also can be reference of before
```

Note:
1. 1 <= words.length <= 2000.
2. 1 <= words[i].length <= 7.
3. Each word has only lowercase letters.

如上所述，对于给定的单词列表 words，进行编码，生成一个参考字符串，以及一个索引列表。对于每个索引，我们将从参考字符串中该索引位置读取直到遇到一个 "#" 字符，对应于单词列表中的单词。求最短参考字符串的长度。

## 思路和实现

对于所有单词，若有单词 B 是 A 的后缀，那么 A 可以作为 B 的参考字符串。因此，去掉所有的后缀，剩余的单词加上分隔符 # 就是参考字符串。

### 1. 后缀删除

按单词列表转换为集合，然后删除所有单词可能的后缀，剩余的单词加上分隔符 # 就是参考字符串。

见 [solution.cpp](solution.cpp)

### 2. Trie

所有后缀单词只需要最长的那个在参考字符串中，用字典树来维护后缀关系，然后求出所有叶子节点对应单词的长度 来求解。

在求叶子节点的长度时，可以用 DFS

``` c++
TC=O(NK), K = 单词平均长度
SC=O(NK)

class Solution {
private:
    // 字典树数据结构
    class Trie {
    public:
        array<Trie*, 26> next = {};
        int wordIdx = -1;
        // 若 hasNext 则不是叶子节点
        bool hasNext = false;
        // 将 word 逆序插入到字典树中
        void insertReverseWord(string& word, int idx) {
            Trie* cur = this;
            // 逆序搜索并创建可能的 Trie Node
            for (int i = word.size() - 1; i >= 0; i--) {
                int nextIdx = word[i] - 'a';
                if (cur->next[nextIdx] == NULL) {
                    cur->next[nextIdx] = new Trie();
                    cur->hasNext = true;
                }
                cur = cur->next[nextIdx];
            }
            // 将 word 的索引保存到叶子节点，本题没用到
            cur->wordIdx = idx;
        }
    };
public:
    Trie* root;
    // 保存结果
    int res;
    
    int minimumLengthEncoding(vector<string>& words) {
        root = new Trie();
        int n = words.size();
        // 将单词插入字典树
        for (int i = 0; i < n; i++) {
            root->insertReverseWord(words[i], i);
        }
        // DFS Trie 根节点
        res = 0;
        dfs(root, 1);

        return res;
    }
    
    void dfs(Trie* cur, int depth) {
        // 叶子节点，res 增加 depth
        if (!cur->hasNext) {
            res += depth;
        }
        // DFS 搜索子节点
        for (int i = 0; i < 26; i++) {
            char c = 'a' + i;
            if (cur->next[i]) {
                dfs(cur->next[i], depth + 1);
            }
        }
    }
};
```

在求叶子节点的长度时，也可以表示单词的节点在插入时维护到 map 中

``` c++
TC=O(NK)
SC=O(NK)

class Solution {
private:
    class Trie {
    public:
        array<Trie*, 26> next = {};
        int wordIdx = -1;
        bool hasNext = false;
    };
public:
    // 维护 Trie中单词节点 -> 深度 的映射
    unordered_map<Trie*, int> leaves;
    
    int minimumLengthEncoding(vector<string>& words) {
        Trie* root = new Trie();
        int n = words.size();
        // 每个单词逆序插入
        for (int i = 0; i < n; i++) {
            Trie* cur = root;
            string& word = words[i];
            for (int i = word.size() - 1; i >= 0; i--) {
                int nextIdx = word[i] - 'a';
                if (cur->next[nextIdx] == NULL) {
                    cur->next[nextIdx] = new Trie();
                    cur->hasNext = true;
                }
                cur = cur->next[nextIdx];
            }
            cur->wordIdx = i;
            // 将单词节点保存到 leaves 中
            leaves.insert({cur, word.size()});
        }
        
        int res = 0;
        for (auto& [leaf, depth] : leaves) {
            // 没有子节点的单词节点 才是 叶子节点
            if (!leaf->hasNext) {
                res += depth + 1;
            }
        }
        
        return res;
    }
};
```
