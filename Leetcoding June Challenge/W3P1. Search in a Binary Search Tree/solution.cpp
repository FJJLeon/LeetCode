#include<util/tree.cpp>

/**
 * recursive
*/
class Solution1 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return nullptr;
        }
        if (val == root->val)
            return root;
        else if (val < root->val)
            return searchBST(root->left, val);
        else
            return searchBST(root->right, val);
    }
};

/**
 * iterative
*/
class Solution2 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root) {
            if (val == root->val)
                return root;
            else if (val < root->val)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }
};
