# 211. Design Add and Search Words Data Structure

## 描述

题面：https://leetcode.com/problems/design-add-and-search-words-data-structure/

字符串通配符匹配，可使用Trie保存添加的字符串

## 实现

### Trie

使用字典树存储字符串，在搜索中实现通配符。

``` c++
|W| = 单词长度
|A| = 字符集大小 = 26
T : 
添加 O(|W|)
匹配 O(|A|^|W|)，待匹配字符全是通配符时出现最差时间复杂度，一般为 O(|W|)
S :
O((Σ|W|) * |A|)

static const int LETTER_NUM = 26;

// Trie 类
class Trie {
public:
    // 标识是字符串结尾
    bool bIsWord = false;
    Trie* children[LETTER_NUM] = {};

    Trie() {}
    
    // 向Trie中添加新字符串
    void add(string word) {
        Trie* cur = this;
        for (auto c : word) {
            if (!cur->children[c - 'a'])
                cur->children[c - 'a'] = new Trie();
            cur = cur->children[c - 'a'];
        }
        cur->bIsWord = true;
    }
    
    // 完全匹配，参考用，本题没用到
    bool perfectMatch(string word) {
        Trie* cur = this;
        for (auto c : word) {
            if (!cur->children[c - 'a'])
                return false;
            cur = cur->children[c - 'a'];
        }
        
        return cur->bIsWord;
    }
    
};


class WordDictionary {
private:
    Trie* root;
public:
    WordDictionary() {
        root = new Trie();
    }
    
    void addWord(string word) {
        root->add(word);
    }
    
    bool search(string word) {
        // return recuMatch1(root, word, 0);
        // return recuMatch2(root, word, 0);
        // return iterMatch(word);
    }
    
    /* 在应用类中实现通配符匹配*/
    // 递归DFS实现
    bool recuMatch1(Trie* cur, string word, int idx) {
        if (idx == word.size()) {
            return cur->bIsWord;
        }
        
        char c = word[idx];
        // 若是通配符，则需要遍历cur所有可行的子节点
        if (c == '.') {
            for (Trie* child : cur->children) {
                // child存在，递归调用返回 true 则匹配成功
                if (child && recuMatch1(child, word, idx + 1))
                    return true;
            }
        }
        // 正常小写字符
        else {
            // 对应 child 存在 且 递归调用返回 true 则匹配成功
            if (cur->children[c - 'a'] && recuMatch1(cur->children[c - 'a'], word, idx + 1))
                return true;
        }
        return false;
    }

    // 递归DFS优化，参考 perfectMatch
    // 对于连续的非通配符字符，可以先迭代，减少递归栈使用
    // 在LC测试中减少了一半的内存使用
    bool recuMatch2(Trie* cur, string word, int idx) {
        // 对于连续的非通配符字符，迭代匹配
        while (idx < word.size() && word[idx] != '.') {
            if (!cur->children[word[idx] - 'a'])
                return false;
            cur = cur->children[word[idx] - 'a'];
            idx++;
        }
        // 是否匹配完
        if (idx == word.size())
            return cur->bIsWord;
        // 存在通配符，再递归调用
        if (word[idx] == '.') {
            for (Trie* child : cur->children) {
                if (child && recuMatch2(child, word, idx + 1))
                    return true;
            }
        }
        
        return false;
    }
    
    // 迭代实现
    bool iterMatch(string word) {
        // 使用栈保存 <当前Trie节点, 下一个字符索引>
        stack<pair<Trie*, int>> s;
        s.push({root, 0});
        
        int n = word.size();
        while (!s.empty()) {
            Trie* cur = s.top().first;
            int idx = s.top().second;
            s.pop();
            // 若已到达末尾，判断是否匹配成功
            if (idx == n) {
                if (cur->bIsWord)
                    return true;
                continue;
            }
            
            char c = word[idx];
            // 通配符，需要将 <所有可行子节点, idx+1> 都入栈
            if (c == '.') {
                for (Trie* child : cur->children)
                    if (child)
                        s.push({child, idx + 1});
            }
            // 正常字符，存在则入栈
            // 注意此处不存在不是直接返回 false
            // 可能有多个通配符候选结果
            else if (cur->children[c - 'a']) {
                s.push({cur->children[c - 'a'], idx + 1});
            }
        }
        
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
```

### 按长度分类

一种暴力优化，将单词按照长度分桶存储，减小搜索时需要匹配的范围

这个方法实际上假设了输入数据中单词长度分布分散。如果输入数据单词长度全部相等，最坏情况就要对所有输入单词逐一匹配，而字典树在这种情况下能利用前缀搜索

不过这种做法可以很快解决输入全是通配符的情况，而字典树复杂度会很高

``` c++
class WordDictionary {
private:
    // 单词长度 -> 该长度单词集合
    unordered_map<int, set<string>> len2words;
    
public:
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        int n = word.size();
        if (len2words.find(n) == len2words.end())
            len2words[n] = set<string>();
        len2words[n].insert(word);
    }
    
    bool search(string word) {
        int n = word.size();
        auto it = len2words.find(n);
        // 不存在该长度单词
        if (it == len2words.end())
            return false;
        // 仅在该长度单词集合中匹配
        for (auto cand : it->second) {
            int i = 0;
            for (i = 0; i < n; i++) {
                char c = word[i];
                // 搜索字符为通配符 或 搜索字符与候选字符相同
                if (c == '.' || c == cand[i])
                    continue;
                else
                    break;
            }
            // 若能匹配到末尾，则匹配成功
            if (i == n)
                return true;
        }
        
        return false;
    }
};
```