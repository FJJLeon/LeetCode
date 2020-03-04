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
 * version 1.1: 
 * Recursive each create 4 vector instances, slow & large memory usage
 * 
 * Runtime: 40 ms
 * Memory Usage: 78.4 MB
*/
class Solution11 {
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
 * version 1.2:
 * still recursive, don't instantiate new vector, just mark with iterator 
 * 
 * Runtime: 20 ms
 * Memory Usage: 23.1 MB
*/
class Solution12 {
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
        
        // iterator of root val in inorder 
        vit rootIt_in = find(in_begin, in_end, rootVal);
        // index of root val in inorder 
        int rootIndex_in = distance(in_begin, rootIt_in);
        
        root->left = buildTreeByIter(pre_begin+1, pre_begin+rootIndex_in+1,
                                    in_begin, rootIt_in);
        root->right = buildTreeByIter(pre_begin+rootIndex_in+1, pre_end,
                                     rootIt_in+1, in_end);
        
        return root;
    }
};


/**
 * version 1.3:
 * base 1.2, use map cache iterator of inorder
 * 
 * Runtime: 12 ms, 97.03%
 * Memory Usage: 23.3 MB, 9.52%
*/
class Solution13 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int len = preorder.size();
        unordered_map<int, vit> inMap(len);
        
        int i;
        vit it;
        for (i=0, it=inorder.begin(); i<len, it<inorder.end(); i++, it++) {
            // use map record <val, inorder_iterator>
            inMap.insert(pair<int, vit>(inorder[i], it));
        }

        return buildTreeByIter(preorder.begin(), preorder.end(), inorder.begin(), inorder.end(), inMap);
    }

private:
    typedef vector<int>::iterator vit;
    TreeNode* buildTreeByIter(vit pre_begin, vit pre_end, vit in_begin, vit in_end, unordered_map<int, vit>& inMap) {
        if (pre_begin == pre_end)
            return NULL;
        
        int rootVal = *pre_begin;
        TreeNode* root = new TreeNode(rootVal);
        if (pre_end - pre_begin == 1 && in_end - in_begin == 1)
            return root;
        
        // access map instead find
        vit rootIt_in = inMap[rootVal];
        int rootIndex_in = rootIt_in - in_begin;
        
        root->left = buildTreeByIter(pre_begin+1, pre_begin+rootIndex_in+1,
                                    in_begin, rootIt_in, inMap);
        root->right = buildTreeByIter(pre_begin+rootIndex_in+1, pre_end,
                                     rootIt_in+1, in_end, inMap);
        
        return root;
    }
};


/**
 * version 2.1:
 * iteration, each construct root to left-most and then repeat
 * 
 * 0. preorder 的第一个是 root 节点，inorder 的第一个是当前左路径的 left-most 节点
 * 1. 循环使用来自 preorder 的节点构造左路径并压栈，直到栈顶元素等于 inorder 的第一个，即左路径构造完成
 * 2. 持续 pop 并与 inorder 当前元素比较（要维护 inorder 的索引），直到两者不相等，即发现了一个离 left-most 最近的右分支，构造右节点（即新路径的根节点）
 * 3. 重复 1、2 直到遍历完 preorder
 * 
 * Runtime: 16 ms 
 * Memory Usage: 21.2 MB
*/
class Solution21 {
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
            // until top of stack(pres) is equal to inorder[j] a.k.a left-most
            while (pres.top() != inorder[j]) {
                pres.push(preorder[i]);
                TreeNode* leftNode = new TreeNode(preorder[i]);
                nodes.top()->left = leftNode;
                nodes.push(leftNode);
                i++;
            }
            // pop stack until top of stack not equal to inorder[j]
            while (!pres.empty() && pres.top() == inorder[j]) {
                pres.pop();
                rootNode = nodes.top();
                nodes.pop();
                j++;
            }
            // loop for next bevel edge
            // now next of preorder is new root while next of inorder if new left-most
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

/**
 * version 2.2:
 * basing version 2.1, remove unnecessary stack of val, simplify code
 * 
 * Runtime: 8 ms, 99.63%
 * Memory Usage: 20.8 MB, 23.81%
*/

class Solution22 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0)
            return NULL;

        // i for index of preorder, j for inorder
        int i = 0, j = 0;

        TreeNode* rootNode = new TreeNode(preorder[i++]), *res = rootNode;
        
        stack<TreeNode *> nodes;
        nodes.push(rootNode);
        
        const int len = preorder.size();
        while (i < len) {
            // dfs for current root to left-most 
            // until top of stack(pres) is equal to inorder[j] a.k.a left-most
            while (nodes.top()->val != inorder[j]) {
                nodes.top()->left = new TreeNode(preorder[i++]);
                nodes.push(nodes.top()->left);
            }
            // pop stack until top of stack not equal to inorder[j]
            while (!nodes.empty() && nodes.top()->val == inorder[j]) {
                rootNode = nodes.top();
                nodes.pop();
                j++;
            }
            // loop for next bevel edge
            // now next of preorder is new root (left child of current rootNode) while next of inorder if new left-most
            if (i < len) {
                rootNode->right = new TreeNode(preorder[i++]);
                nodes.push(rootNode->right);
            }
        }
        
        return res;
    }
};