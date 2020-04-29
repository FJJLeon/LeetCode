#include"util\tree.cpp"
#include<math.h>
#include<stack>
#include<unordered_map>

using namespace std;

/**
 * recursive traverse
 * use max{root, left + root, right + root, left + root + right, maxSum} update maxSum
 * use max{root, left + root, right + root} as return value
 * 
 * Runtime: 32 ms, faster than 62.06%, O(N)
 * Memory Usage: 28.5 MB, less than 6.06%, O(H), H for height of tree
*/
class Solution11 {
public:
    int maxPathSum(TreeNode* root) {
        traverse(root);
        return maxSum;
    }
private:
    int maxSum = INT_MIN;
    int traverse(TreeNode* root) {
        if (!root)
            return INT_MIN;

        int left = traverse(root->left);
        int right = traverse(root->right);
        // 用 max{root, left + root, right + root, left + root + right} 更新 maxSum
        // 但是返回值不能包括 left + root + right， 因为这条path 不能再和其他 祖先 相连
        // LRPathMax = max(INT_MIN, left + right + root)
        int LRPathMax = INT_MIN;
        // RootAsEndPathMax = max{root, left + root, right + root}
        int RootAsEndPathMax = root->val;
        // 这里处理返回值为 INT_MIN 的情况，直接上述 max 表达式会出现 INT_MIN 加一个负数导致 overflow 的情况，考虑仅有一个节点 [-3]
        // 只有 left 或者 right 是正数才对 max 表达式可能有贡献
        // 全是正数
        if (left > 0 && right > 0) {
            LRPathMax = left + right + root->val;
            RootAsEndPathMax = max(left, right) + root->val;
        }
        // 不全是正数
        else if (left > 0) {
            RootAsEndPathMax = left + root->val;
        }
        else if (right > 0) {
            RootAsEndPathMax = right + root->val;
        }
        // 更新全局 maxSum
        int nodeMax = max(LRPathMax, RootAsEndPathMax);
        maxSum = max(maxSum, nodeMax);
        // 返回值不能包括 left + root + right
        return RootAsEndPathMax;
    }
};
/**
 * trick
 * 由于 children 返回负数对于 father 的更新是没有贡献的，不如全部返回非负数
 * 
 * Runtime: 28 ms, faster than 87.00%
 * Memory Usage: 28.6 MB, less than 6.06%
*/
class Solution12 {
public:
    int maxPathSum(TreeNode* root) {
        traverse(root);
        return maxSum;
    }
private:
    int maxSum = INT_MIN;
    int traverse(TreeNode* root) {
        if (!root)
            return 0;

        int left = traverse(root->left);
        int right = traverse(root->right);
        // 用 max{root, left + root, right + root, left + root + right} 更新 maxSum
        // 但是考虑到 left、right 是非负的，直接用 left + right + root 更新即可
        maxSum = max(maxSum, left + right + root->val);
        // 若该 node 返回值会是负数，则返回 0
        int res = max(left, right) + root->val;
        return res > 0 ? res : 0;
    }
};


/**
 * iterative solution
 * save postOrder nodes first, then traverse by caching children value
 * 
 * Runtime: 60 ms, faster than 9.36%, O(N), slow however
 * Memory Usage: 31.5 MB, less than 6.06%, O(2*N) = O(N)
*/
class Solution2 {
public:
    int maxPathSum(TreeNode* root) {
        stack<TreeNode*> postOrder;
        getPostOrder(root, postOrder);
        
        int maxSum = INT_MIN;
        unordered_map<TreeNode*, int> cache;
        cache.insert({nullptr, 0});
        // post order traverse
        while (!postOrder.empty()) {
            TreeNode* t = postOrder.top();
            postOrder.pop();
            // when ancestor meeted, its children value has been cached
            int left = cache[t->left];
            int right = cache[t->right];
            maxSum = max(maxSum, left + right + t->val);
            cache[t] = max(0, max(left, right) + t->val);
        }
        
        return maxSum;
    }
private:
    void getPostOrder(TreeNode* root, stack<TreeNode*> &postOrder) {
        stack<TreeNode*> s;
        s.push(root);
        
        while (!s.empty()) {
            TreeNode* t = s.top();
            s.pop();
            postOrder.push(t);
            // right first in, last out
            if (t->right)
                s.push(t->right);
            if (t->left)
                s.push(t->left);
        }
        
    }
};