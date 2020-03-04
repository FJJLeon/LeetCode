#include<bits/stdc++.h>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * version 1:
 * recursive
 * 
 * Runtime: 8 ms
 * Memory Usage: 14.9 MB
 */
class Solution1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        fs(root, 0, res);
        return res;
    }
private:
    void fs(TreeNode* node, int level, vector<vector<int>>& v) {
        if (node == NULL) {
            return;
        }
        
        if (v.size() == level) {
            v.push_back(vector<int>());
        }
        v[level].push_back(node->val);
        fs(node->left, level+1, v);
        fs(node->right, level+1, v);
    } 
};

/**
 * version 2.1:
 * iterative, use queue (node, level)
 * 
 * Runtime: 8 ms
 * Memory Usage: 13.7 MB
 */ 
class Solution21 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));
        int curr = 0;
        
        while (!q.empty()) {
            
            int level = q.front().second;
            while (level == curr) {
                TreeNode* n = q.front().first;
                q.pop();
                if (n != NULL) {
                    q.push(make_pair(n->left, level+1));
                    q.push(make_pair(n->right, level+1));
                    
                    if (res.size() == curr) {
                        res.push_back(vector<int>());
                    }
                    res[curr].push_back(n->val);
                }
                
                level = q.front().second;
            }
            
            curr++;            
        }
        
        return res;
    }
};


/**
 * version 2.2:
 * iterative, use queue, no level
 * 
 * Runtime: 4 ms, 93.77%
 * Memory Usage: 12.9 MB, 100.00%
 */ 
class Solution22 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;
        
        queue<TreeNode*> q;
        q.push(root);

        vector<int> tmpV;
        while (!q.empty()) {
            int curLen = q.size();
            
            
            TreeNode* tmpNode;
            for (int i=0; i<curLen; i++) {
                tmpNode = q.front();
                q.pop();
                tmpV.push_back(tmpNode->val);
                if (tmpNode->left)
                    q.push(tmpNode->left);
                if (tmpNode->right)
                    q.push(tmpNode->right);
            }
            res.push_back(tmpV);      
            tmpV.clear();    
        }
        
        return res;
    }
};