#include<vector>
#include<map>

#include<util/tree.cpp>

using namespace std;


/**
 * find last elem of postorde in inorder, this is the root
 * recursive in right subtree and left subtree
 * 
 * use map record index of inorder element to reduce find time
 * 
 * Runtime: 20 ms, faster than 82.55%, O(N)
 * Memory Usage: 24.1 MB, less than 34.82%, O(N)
*/
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0)
            return nullptr;
        
        inorder_index = map<int, int>();
        for (int i = 0; i < inorder.size(); ++i)
            inorder_index[inorder[i]] = i;
        post = postorder;
        
        return rec(0, inorder.size() - 1);
    }
private:
    map<int, int> inorder_index;
    vector<int> post;
        
    TreeNode* rec(int low, int high) {
        if (low > high)
            return nullptr;
        
        TreeNode* r = new TreeNode(*post.rbegin());
        post.pop_back();
        
        int mid = inorder_index[r->val];
        
        r->right = rec(mid + 1, high);
        r->left  = rec(low, mid - 1);
        
        return r;
    }
};