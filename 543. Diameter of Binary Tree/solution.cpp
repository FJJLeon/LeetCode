#include"util/tree.cpp"
#include<limits.h>
#include<algorithm>
#include<unordered_map>
#include<stack>

using namespace std;

/**
 * recursive, DFS from root
 * get height of left child and right child for each node
 * 
 * Runtime: 8 ms, faster than 90.27%, O(N)
 * Memory Usage: 17.6 MB, less than 100.00%, O(H)
*/
class Solution {
private:
    int maxDiameter;
    int dfs(TreeNode* node) {
        if (!node)
            return 0;
        int leftHeight = dfs(node->left);
        int rightHeight = dfs(node->right);
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);
        // return height of this node
        return max(leftHeight, rightHeight) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        dfs(root);
        
        return maxDiameter;
    }
};


/**
 * iterative
 * 
 * Runtime: 16 ms, faster than 33.00%, O(N)
 * Memory Usage: 18.8 MB, less than 100.00%, O(N)
*/
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = 0;
        // save height of each node
        unordered_map<TreeNode*, int> height;
        // dfs stack, <node, visited>
        stack<pair<TreeNode*, bool> > s;
        s.push(make_pair(root, false));
        
        while (!s.empty()) {
            auto p = s.top();
            s.pop();
            TreeNode* node = p.first;
            if (!node)
                continue;
            // not visited before
            if (p.second == false) {
                // father should be pushed again and marked visited
                s.push(make_pair(node, true));

                s.push(make_pair(node->left, false));
                s.push(make_pair(node->right, false));
            }
            // visited
            else {
                int leftHeight = height[node->left];
                int rightHeight = height[node->right];
                height[node] = max(leftHeight, rightHeight) + 1;
                maxDiameter = max(maxDiameter, leftHeight + rightHeight);
            }
        }
        
        return maxDiameter;
    }
};
