#include"util/tree.cpp"
#include<vector>
#include<stack>

using namespace std;

/**
 * BST stack store former node
 * 
 * Runtime: 4 ms, faster than 86.93%, O(N)
 * Memory Usage: 10.7 MB, less than 95.24%, O(H)
*/
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> s;
        s.push(root);
        for (int i = 1; i < preorder.size(); ++i) {
            if (preorder[i] < s.top()->val) {
                s.top()->left = new TreeNode(preorder[i]);
                s.push(s.top()->left);
            }
            else {
                // record his father, or poped
                TreeNode* father;
                while (!s.empty() && preorder[i] > s.top()->val) {
                    father = s.top();
                    s.pop();
                }
                father->right = new TreeNode(preorder[i]);
                s.push(father->right);
            }
        }
        return root;
    }
};
