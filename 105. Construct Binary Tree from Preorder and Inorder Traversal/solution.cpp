/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
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
        
        // i for index of preorder, while j for inorder
        int i = 1, j = 0;
        const int len = preorder.size();
        while (i < len) {
            while (preorder[i-1] != inorder[j]) {
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