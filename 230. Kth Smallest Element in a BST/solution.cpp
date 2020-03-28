#include"util/tree.cpp"
#include<stack>

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
 * My solution, simulate, too bad
 * 
 * Runtime: 24 ms, faster than 46.93%
 * Memory Usage: 19.2 MB, less than 100.00%
*/
class Solution1 {
public:
    int kthSmallest(TreeNode* root, int k) {
        
        stack<TreeNode*> s;
        s.push(root);
        
        int c = 0;
        TreeNode* t;
        while(!s.empty()) {
            // traverse left-bottom
            while(s.top()->left)
                s.push(s.top()->left);
            if (++c == k)
                return s.top()->val;
            t = s.top();
            s.pop();

            // traverse right if exist
            if (t->right) {
                s.push(t->right);
            }
            else {
                // pop until right exist
                while (!s.empty() && !s.top()->right) {
                    if (++c == k)
                        return s.top()->val;
                    s.pop();
                }
                // traverse right if exist
                if (!s.empty()) {
                    if (++c == k)
                        return s.top()->val;
                    t = s.top();
                    s.pop();
                    s.push(t->right);
                }
            }
        }
        
        return -1;
    }
};

/**
 * inorder traverse of BST is ascending order sort
 * 
 * Runtime: 16 ms, faster than 96.25%
 * Memory Usage: 19.3 MB, less than 100.00%
*/
class Solution2 {
public:
    int count;
    int result;
    int kthSmallest(TreeNode* root, int k) {
        count = 0;
        inorder(root, k);
        return result;
    }

private:
    void inorder(TreeNode* root, int k) {
        // recursive inorder traverse: left -> self - > right
        // time: O(N)
        // space: O(H), H = height of BST for recursive stack
        if (root->left)
            inorder(root->left, k);
        if (++count == k)
            result = root->val;
        if (root->right)
            inorder(root->right, k);
    }
};

class Solution3 {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> s;
        // iterative inorder traverse
        // time: O(H + k), H = height of BST, O(logN + k) ~ O(N + k)
        // space: O(H + k)
        while (!s.empty() || root) {
            // push until left-most
            if (root) {
                s.push(root);
                root = root->left;
            }
            // pop and check
            else {
                root = s.top();
                s.pop();
                if (--k == 0)
                    return root->val;
                root = root->right;
            }
        }
        return -1;
    }
};