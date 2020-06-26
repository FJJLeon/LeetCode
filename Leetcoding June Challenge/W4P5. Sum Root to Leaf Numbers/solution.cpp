#include<util/tree.cpp>

/**
 * recursive DFS with prefix number
 * when meeting the leaf node, add to global variable [result] (or reference variable)
 * 
 * Runtime: 4 ms, faster than 83.40%, O(N)
 * Memory Usage: 12.5 MB, less than 67.87%, O(H)
*/
class Solution {
private:
    int result;
    void sumPath(TreeNode* root, int num) {
        if (!root)
            return;
        num = 10 * num + root->val;
        if (!root->left && !root->right) {
            result += num;
        }
        else {
            sumPath(root->left, num);
            sumPath(root->right, num);
        }
    }
public:
    int sumNumbers(TreeNode* root) {
        result = 0;
        sumPath(root, 0);
        return result;
    }
};
