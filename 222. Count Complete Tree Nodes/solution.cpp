#include<util/tree.cpp>
#include<math.h>

/**
 * for a complete binary tree, height can be gotten by traversing left node
 * check height of left and right node:
 * a. == -> left subtree must be perfect(full), while right is complete
 * b. != -> left subtree is complete, while right is perfect
 * number of nodes for perfect binary tree is 2^h - 1
 * 
 * Runtime: 40 ms, faster than 84.08%, O(N)
 * Memory Usage: 31.2 MB, less than 15.02%, O(H)
*/
class Solution {
private:
    int completeHeight(TreeNode* root) {  
        int h = 0;
        while (root) {
            ++h;
            root = root->left;
        }
        return h;
    }
public:
    int countNodes(TreeNode* root) {
        if (root == NULL)
            return 0;
        int leftHeight = completeHeight(root->left),
            rightHeight = completeHeight(root->right);
        if (leftHeight == rightHeight)
            return pow(2, leftHeight) + countNodes(root->right);
        else
            return countNodes(root->left) + pow(2, rightHeight);
    }
};
