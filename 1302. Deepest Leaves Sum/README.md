# 1302. Deepest Leaves Sum

## 题目

题面：https://leetcode.com/problems/deepest-leaves-sum/

二叉树，求和所有最深层的节点值

## 实现

### DFS

在 DFS 过程中带着深度，每当见到更深层次时重置和

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int maxLevel, sum;
    int deepestLeavesSum(TreeNode* root) {
        maxLevel = 0, sum = 0;
        dfs(root, 0);
        return sum;
    }
    
    void dfs(TreeNode* root, int level) {
        if (!root)
            return;
        // 更深层次，重置 sum
        if (level > maxLevel) {
            maxLevel = level;
            sum = 0;
        }
        // 等于当前见过的最深层次，累加
        if (level == maxLevel) {
            sum += root->val;
        }
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    }
};
```

### LevelOrder

层序遍历，每层更新和

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            // 新的层次，重置和
            res = 0;
            // 遍历层
            for (int i = q.size(); i > 0; i--) {
                TreeNode* cur = q.front(); q.pop();
                res += cur->val;
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }
        return res;
    }
};
```