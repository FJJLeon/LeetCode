#include<iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/**
 * iterative
 * 
 * Runtime: 116 ms, 91.67%
 * Memory Usage: 49.1 MB, 6.25%
*/
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* father = root, *last;
        bool flag;
        while (father) {
            last = father;
            if (val > father->val) {
                flag = true;
                father = father->right;
            } else {
                flag = false;
                father = father->left;
            }
        }
        
        if (flag) {
            last->right = new TreeNode(val);
        } else {
            last->left = new TreeNode(val);
        }
        
        return root;
    }
};