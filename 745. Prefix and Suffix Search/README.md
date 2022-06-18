# 745. Prefix and Suffix Search

## 题目

题面：https://leetcode-cn.com/problems/prefix-and-suffix-search/

给定 前缀 后缀，求对应的字符串，若有多个，返回索引大的。

## 实现

字典树

Hint 提示难以想到，到底是 Hard。将前缀和后缀在建树时合并，即对于字符串 "test"，在字典树中存储 "#test", "t#test", "st#test", "est#test", "test#test"，搜索时只需搜索 suffix+"#"+prefix 即可。

``` c++
class Trie {
public:
    array<Trie*, 27> next {};
    bool isWord;
    int pathLargestIdx;
    
    Trie() {
        isWord = false;
        pathLargestIdx = -1;
    }
    
    void insert(string& s, int idx) {
        Trie* t = this;
        int nextIdx;
        for (char c : s) {
            if (c == '#')
                nextIdx = 26;
            else
                nextIdx = c - 'a';
            
            if (t->next[nextIdx] == NULL)
                    t->next[nextIdx] = new Trie();
            t = t->next[nextIdx];
            
            if (t->pathLargestIdx == -1) {
                t->pathLargestIdx = idx;
            }
        }
        
        if (!t->isWord) {
            t->isWord = true;
        }
    }
    
    int search(string& s) {
        Trie* t = this;
        int nextIdx;
        for (char c : s) {
            if (c == '#')
                nextIdx = 26;
            else
                nextIdx = c - 'a';
            
            if (t->next[nextIdx] == NULL)
                return -1;
             t = t->next[nextIdx];
        }
        
        return t->pathLargestIdx;
    }
};


class WordFilter {
public:
    Trie* root = NULL;
    WordFilter(vector<string>& words) {
        root = new Trie();
        int n = words.size();
        for (int i = n - 1; i >= 0; i--) {
            int len = words[i].size();
            string merge = "#" + words[i];
            root->insert(merge, i);
            for (int j = len - 1; j >= 0; j--) {
                merge = words[i][j] + merge;
                root->insert(merge, i);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        string query = suffix + "#" + prefix;
        return root->search(query);
    }
};
```