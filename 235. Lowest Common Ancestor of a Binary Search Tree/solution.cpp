#include"../util/tree.cpp"
#include<string>

using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


/**
 * make use of BST
 * iterative 
 * 
 * Runtime: 40 ms, faster than 51.10%, O(N)
 * Memory Usage: 23.6 MB, less than 100.00%, O(1)
*/
class Solution1 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int pV = p->val, qV = q->val;
        
        // start search from root
        TreeNode *n = root;
        while (n) {
            if (pV < n->val && qV < n->val) {
                // both p and q less than current parent
                n = n->left;
            }
            else if (pV > n->val && qV > n->val) {
                // both p and q greater than current parent
                n = n->right;
            }
            else {
                // one less, one greater, LCA found 
                return n;
            }
        }
        return NULL;
    }
};

/**
 * recursive
 * 
 * Runtime: 40 ms, faster than 51.10%, O(N)
 * Memory Usage: 23.2 MB, less than 100.00%, O(N), recursive stack might be O(N) due to unbalanced BST
*/
class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        int rootVal = root->val;
        int pVal = p->val, qVal = q->val;
        
        if (pVal < rootVal && qVal < rootVal)
            // both p and q less than current parent
            return lowestCommonAncestor(root->left, p, q);
        else if (pVal > rootVal && qVal > rootVal)
            // both p and q greater than current parent
            return lowestCommonAncestor(root->right, p, q);
        else
            // one less, one greater, LCA found
            return root;
        
        return NULL;
    }
};
