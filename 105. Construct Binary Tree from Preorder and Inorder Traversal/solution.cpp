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
 * the first element of preorder is root, mark it in inorder
 * before which is left subtree of root, while after which is right
 * 
 * version 1: 
 * Recursive each create 4 vector instances, slow & large memory usage
 * 
 * Runtime: 40 ms
 * Memory Usage: 78.4 MB
*/
class Solution1 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0)
            return NULL;
        int rootVal = preorder[0];
        TreeNode* root = new TreeNode(rootVal);
        if (preorder.size() == 1 && inorder.size() == 1)
            return root;
        
        auto rootIt_in = find(inorder.begin(), inorder.end(), rootVal);
        auto rootIndex_in = distance(inorder.begin(), rootIt_in);
        
        vector<int> left_pre = vector<int>(preorder.begin()+1, preorder.begin()+rootIndex_in+1),
                    left_in = vector<int>(inorder.begin(), rootIt_in),
                    right_pre = vector<int>(preorder.begin()+rootIndex_in+1, preorder.end()),
                    right_in = vector<int>(rootIt_in+1, inorder.end());
        
        root->left = buildTree(left_pre, left_in);
        root->right = buildTree(right_pre, right_in);
        
        return root;
    }
};

/**
 * version 2:
 * still recursive, don't instantiate new vector, just mark with iterator 
 * 
 * Runtime: 20 ms
 * Memory Usage: 23.1 MB
*/
class Solution2 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreeByIter(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }
private:
    typedef vector<int>::iterator vit;
    TreeNode* buildTreeByIter(vit pre_begin, vit pre_end, vit in_begin, vit in_end) {
        if (pre_begin == pre_end)
            return NULL;
        
        int rootVal = *pre_begin;
        TreeNode* root = new TreeNode(rootVal);
        if (pre_end - pre_begin == 1 && in_end - in_begin == 1)
            return root;
        
        vit rootIt_in = find(in_begin, in_end, rootVal);
        int rootIndex_in = distance(in_begin, rootIt_in);
        
        root->left = buildTreeByIter(pre_begin+1, pre_begin+rootIndex_in+1,
                                    in_begin, rootIt_in);
        root->right = buildTreeByIter(pre_begin+rootIndex_in+1, pre_end,
                                     rootIt_in+1, in_end);
        
        return root;
    }
};

/**
 * version 3:
 * iteration, each construct root to left-most and then repeat
 * 
 * Runtime: 16 ms 
 * Memory Usage: 21.2 MB
*/
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0)
            return NULL;

        int rootVal = preorder[0];
        TreeNode* rootNode = new TreeNode(rootVal), *res = rootNode;
        
        stack<int> pres;
        pres.push(rootVal);
        stack<TreeNode *> nodes;
        nodes.push(rootNode);
        
        // i for index of preorder, j for inorder
        int i = 1, j = 0;
        const int len = preorder.size();
        while (i < len) {
            // dfs for current root to left-most
            while (pres.top() != inorder[j]) {
                pres.push(preorder[i]);
                TreeNode* leftNode = new TreeNode(preorder[i]);
                nodes.top()->left = leftNode;
                nodes.push(leftNode);
                i++;
            }
            // now top of stack(pres) is equal to inorder[j] a.k.a left-most
            while (!pres.empty() && pres.top() == inorder[j]) {
                pres.pop();
                rootNode = nodes.top();
                nodes.pop();
                j++;
            }
            // loop for next bevel edge
            if (i < len) {
                int rightVal = preorder[i];
                pres.push(rightVal);
                TreeNode* rightNode = new TreeNode(rightVal);
                rootNode->right = rightNode;
                nodes.push(rightNode);
                i++;
            }
        }
        
        return res;
    }
};