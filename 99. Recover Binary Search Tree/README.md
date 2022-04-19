# 99. Recover Binary Search Tree

## 描述

题面：https://leetcode.com/problems/recover-binary-search-tree/

一棵 BST 中交换了两个节点，恢复之

## 思路与实现

BST 中交换了两个节点，这会导致在BST的中序遍历顺序中，出现非单调上升的情况。中序遍历过程中找到出现错误的节点对，交换之。比如，
```
     5      中序遍历
    / \      1 - 3 - 4 - 5 - 6
   3   6
  / \
 1   4
            两对降序节点，第一对的前者 和 第二对的后者 为错误对
     5       1 - (6 - 4) - (5 - 3)
    / \           ↑             ↑
  (6) (3)   
  / \
 1   4
            一对降序节点，即为错误对
    (4)       1 - 3 - (5 - 4) - 6
    / \                ↑   ↑    
   3   6         
  / \
 1  (5)
```

### 1. 额外空间中序遍历

递归实现

``` c++
TC = O(N)
SC = O(H)，递归栈空间

class Solution {
public:
    // 用于记录被错误交换的两个节点
    TreeNode* m1, *m2;
    // 记录中序遍历中的前趋节点
    TreeNode* last;
    void recoverTree(TreeNode* root) {
        inorder(root);
        swap(m1->val, m2->val);
    }
    
    void inorder(TreeNode* root) {
        if (!root)
            return;
        // 中序遍历左子树
        inorder(root->left);
        // 如果中序遍历前趋节点值存在，且大于当前节点值，即为错误的降序对
        if (last && last->val > root->val) {
            // 是第一对，记录前者
            if (!m1)
                m1 = last;
            // 不管是第一对还是第二对，记录后者
            m2 = root;
        }
        // 更新前趋节点
        last = root;
        // 中序遍历右子树
        inorder(root->right);
    }
};
```

### 2. Morris 遍历

无论递归还是栈迭代实现，都有额外空间，题目的 follow up 希望使用 O(1) 空间，可能是一定要使用Morris遍历

``` c++
TC = O(N)
SC = O(1)

class Solution {
public:
    // 获取中序遍历前趋节点
    TreeNode* getPrec(TreeNode* root) {
        TreeNode* prec = root->left;
        while (prec->right && prec->right != root)
            prec = prec->right;
        return prec;
    }
    
    void recoverTree(TreeNode* root) {
        // 用于记录被错误交换的两个节点
        TreeNode* m1{nullptr}, *m2{nullptr};
        // 记录中序遍历中的前趋节点，注意区分 last 和 prec
        TreeNode* last{nullptr};
        // Morris 遍历所需的前趋节点
        TreeNode* prec;
        while (root) {
            // 1.若存在左子树
            if (root->left) {
                // 找到前趋节点
                prec = getPrec(root);
                // 1.1.若前趋节点右孩子为空，即左子树尚未遍历过
                if (!prec->right) {
                    // 则前趋节点右连当前节点
                    prec->right = root;
                    // 遍历左子树
                    root = root->left;
                }
                // 1.2.若前趋节点右孩子不为空（只能为当前节点），即左子树已经遍历过
                else {
                    // 如果中序遍历前趋节点值存在，且大于当前节点值，即为错误的降序对
                    if (last && last->val > root->val) {
                        // 是第一对，记录前者
                        if (!m1)
                            m1 = last;
                        // 不管是第一对还是第二对，记录后者
                        m2 = root;
                    }
                    // 断开前趋节点的右连
                    prec->right = nullptr;
                    // 更新 last
                    last = root;
                    // 遍历右子树
                    root = root->right;
                }
            }
            // 2.不存在左子树
            else {
                // 同上，处理当前节点
                if (last && last->val > root->val) {
                    if (!m1)
                        m1 = last;
                    m2 = root;
                }
                // 更新 last
                last = root;
                // 遍历右子树
                root = root->right;
            }
        }
        
        swap(m1->val, m2->val);
    }
};
```

为什么这样的遍历是O(N)时间复杂度？直观上 **getPrec** 函数的遍历过程会使得整体时间复杂度变成 O(NH)，一般为 O(NLogN)。但是，考虑全局，一棵N节点的BST，一共有N-1条边。**getPrec** 函数整体上会遍历所有右指针路径两次（一次在遍历左子树前，一次在遍历完左子树后），故整体该函数时间复杂度小于 O(2N)，不会增加整体时间复杂度。 