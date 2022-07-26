# 236. Lowest Common Ancestor of a Binary Tree

## 题目

题面：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/

找到二叉树两个节点的的最近公共祖先 LCA。

## 实现

DFS 搜索，对于每个节点，记录当前节点、左子树、右子树中是 p 或 q 节点的数量，当数量第一次为 2 时，该当前节点就是 LCA。

``` c++
TC=O(N)
SC=O(H) = O(N)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p->val, q->val);
        return lca;
    }
    
    TreeNode* lca;
    int dfs(TreeNode* cur, int p, int q) {
        if (!cur)
            return 0;
        // 当前节点是否 p 或 q 中的一个
        int t = (cur->val == p) + (cur->val == q);
        // DFS 左右子树，累加返回值
        t += dfs(cur->left, p, q) + dfs(cur->right, p, q);
        // t 第一次等于 2（即全局变量 lca 为空），则当前节点为 LCA
        // 注意 LCA 的所有祖先返回值都是 2
        if (t == 2 && !lca)
            lca = cur;
        return t;
    }
};
```

题设说二叉树节点中存的值唯一，可以直接比较值，当然比较指针值比较好。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return lca;
    }
    
    TreeNode* lca;
    int dfs(TreeNode* cur,  TreeNode* p,  TreeNode* q) {
        if (!cur)
            return 0;
        int t = (cur == p) + (cur == q);
        t += dfs(cur->left, p, q) + dfs(cur->right, p, q);
        if (t == 2 && !lca)
            lca = cur;
        return t;
    }
};
```
