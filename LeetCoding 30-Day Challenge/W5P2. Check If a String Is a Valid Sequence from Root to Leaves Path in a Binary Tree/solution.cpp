#include"util/tree.cpp"
#include<vector>
#include<stack>

using namespace std;

/**
 * recursive DFS
 * for each path node, check node->val == arr[depth]
 * for last index of arr, check node is leaf
 * 
 * Runtime: 84 ms, O(max(M,N)), M = node number, N = arr.size()
 * Memory Usage: 48.9 MB, O(H)
*/
class Solution {
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return checkNode(root, arr, 0);
    }
private:
    bool checkNode(TreeNode* root, vector<int>& target, int depth) {
        if (!root)
            return false;
        // not match, this path invalid -> early return, 
        if (root->val != target[depth])
            return false;
        // target get final index, check leaf node
        if (depth == target.size() - 1)
            return !root->left && !root->right;
        // DFS
        return checkNode(root->left, target, depth + 1) || checkNode(root->right, target, depth + 1);
    }
};

/**
 * iterative DFS, use stack save {node, depth}
 * 
 * Runtime: 96 ms, O(max(M,N))
 * Memory Usage: 48.9 MB, O(M)
*/
class Solution12 {
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        int len = arr.size();
        
        stack<pair<TreeNode*, int>> s;
        s.push(pair(root, 0));
        while (!s.empty()) {
            TreeNode* r = s.top().first;
            int depth = s.top().second;
            s.pop();
            // not match, this path invalid
            if (r->val != arr[depth])
                continue;
            // get final index, check leaf node
            if (depth == len - 1) {
                if (!r->left && !r->right)
                    return true;
                else
                    continue;
            }
            // DFS, push left and right to stack
            if (r->left)
                s.push(pair(r->left, depth + 1));
            if (r->right)
                s.push(pair(r->right, depth + 1));
        }
        return false;
    }
};
