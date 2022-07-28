# 114. Flatten Binary Tree to Linked List

## 题目

题面：https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/

把二叉树用右指针展开成链表

## 实现

链表中节点的顺序即为二叉树前序遍历的顺序，一个显然的做法是在前序遍历过程中用一个容器按顺序保存访问节点，最后按容器中的顺序重新构建二叉树。

我们实际上不需要显式得这样做，对于每个节点来说，我们需要把左孩子放到右孩子的位置上，同时把右孩子连接到左孩子的 RightMost 节点的右指针上，这是一个递归的过程。

从最左节点往右上方向看，每个左子树右分支（值左孩子到RightMost的斜线）都被插入到父节点和父节点的右孩子之间。

一种做法是对左右孩子进行递归展平，我们认为完成递归调用后，左子树和右子树都已经分别是一个链表。此时，找到左子树的RightMost节点进行重新连接。

``` c++
TC=O(2N)=T(N)
SC=O(H)

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root)
            return;
        
        TreeNode *l = root->left, *r = root->right;
        root->left = nullptr;
        // 递归展平左右子树
        flatten(l);
        flatten(r);
        // 若无左子树，则直接返回
        if (!l)
            return;
        // 找到左子树的RightMost节点
        TreeNode *rm = l;
        while (rm->right != nullptr)
            rm = rm->right;
        // 重新连接，root -> l -> rm -> r
        root->right = l;
        rm->right = r;
    }
};
```

迭代写法，这实际上是一个自顶向下的过程，将根节点的左子斜线（从左孩子到RightMost）插入根节点到右孩子，在循环中往右迭代，若发现有左节点则进行插入，直到没有左节点为止。

``` c++
TC=O(2N)=T(N)
SC=O(H)

class Solution {
public:
    void flatten(TreeNode* root) {
        while (root) {
            if (root->left) {
                // 找到左子树的RightMost节点
                TreeNode* rm = root->left;
                while (rm->right)
                    rm = rm->right;
                // 重新连接 root -> left -> rm -> right
                rm->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
            // 往右迭代
            root = root->right;
        }
        
    }
};
```

以上实现过程中实际上访问了所有节点两遍，一遍在遍历访问中，一遍在寻找RightMost节点的过程中。而我们可以消除寻找 RightMost 节点的过程，可以实现辅助函数用返回值记录。

在 DFS 过程中，想对于某个节点返回 RightMost 节点，进行重新连接后，需要在左右孩子的递归返回值和当前节点中选择一个作为当前节点的返回值，按照递归右 - 递归左 - 当前节点 的顺序返回一个非空值。

``` c++
TC=O(N)
SC=O(H)

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root)
            return;
        dfs(root);
        return;
    }
    
    TreeNode* dfs(TreeNode* root) {
        if (!root)
            return root;
        // 对左右子树递归调用
        TreeNode *l = dfs(root->left), *r = dfs(root->right);
        // 若有左子树，则进行重新连接
        if (l) {
            l->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        // 按照递归右 - 递归左 - 当前节点 的顺序返回一个非空值，作为当前节点的返回值即父节点的左孩子的RightMost节点
        return r ? r : l ? l : root;
    }
};
```
