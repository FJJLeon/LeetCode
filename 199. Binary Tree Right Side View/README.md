# 199. Binary Tree Right Side View

## 题目

题面：https://leetcode-cn.com/problems/binary-tree-right-side-view/

一棵二叉树，从右侧看过去，返回从上到下能看到的数，实际上数组中依次是每层最右侧的值。

## 思路与实现

### 1. BFS 层序遍历

既然实际上是每层最右侧的值，显然可以使用层序遍历，只保存每层最后一个节点的值。

使用队列辅助进行 BFS 遍历

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root)
            return res;
        
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            // 记录当前层遍历的节点
            TreeNode* cur;
            // 每层只操作 queue n 次，在操作过程中 queue size 会变化
            for (int n = q.size(); n > 0; n--){
                cur = q.front(); q.pop();
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            // 此时 cur 是当前层的最后一个节点，将其值加入结果数组
            res.push_back(cur->val);
        }
            
        return res;
    }
};
```

### 2. 中右左 DFS 遍历

除了 BFS，也可以用 DFS 遍历，但是需要注意的是遍历顺序是一种反向前序遍历，按照中右左的顺序进行遍历，这样保证了每个深度的节点都是最右侧的先被访问。

若发现此时结果数组的大小和深度一致（取决于深度初始值），则说明这是当前层第一个被访问的即最右侧的节点，需要将其值加入结果数组。

``` c++
TC=O(N)
SC=O(H)

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, res, 0);
        return res;
    }
    void dfs(TreeNode* root, vector<int>& res, int depth) {
        if (!root)
            return;
        if (depth == res.size()) {
            res.push_back(root->val);
        }
        dfs(root->right, res, depth + 1);
        dfs(root->left, res, depth + 1);
    }
};
```
