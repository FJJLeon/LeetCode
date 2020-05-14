#include<string>
#include<memory.h>

using namespace std;

const int alphaCount = 26;
// trie node definition
struct TrieNode {
    // mark a word end
    bool isEndWord;
    // all lowercase alphabet path
    TrieNode *child[alphaCount];
    TrieNode() {
        isEndWord = false;
        /* // replace with memset
        for (int i = 0; i < alphaCount; ++i)
                child[i] = NULL;
        */
        memset(child, 0, sizeof(child));
    }
};

/**
 * reference: http://zh.wikipedia.org/wiki/Trie
 * 
 * Runtime: 100 ms
 * Memory Usage: 43.5 MB
*/
class Trie {
private:
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->child[c - 'a'] == NULL) {
                cur->child[c - 'a'] = new TrieNode();
            }
            cur = cur->child[c - 'a'];
        }
        cur->isEndWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->child[c - 'a'])
                cur = cur->child[c - 'a'];
            else
                return false;
        }
        return cur->isEndWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            if (cur->child[c - 'a'])
                cur = cur->child[c - 'a'];
            else
                return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
