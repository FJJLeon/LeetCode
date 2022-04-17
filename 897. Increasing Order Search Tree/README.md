# 897. Increasing Order Search Tree

## 描述

题面：https://leetcode.com/problems/increasing-order-search-tree/

使用 right 指针把 BST 转换成单链表，单链表的顺序即为中序遍历的顺序

## 思路与实现

### 1. 基于 Morris 遍历

类似 Morris 遍历，从根节点 R 出发，找到前趋节点 P（左子树的RightMost叶子节点），使得节点 P 右连 R，递归调用左子树根节点；对于右子树，同样递归调用右子树根节点，并使 R 右连返回值（返回值为子树的 LeftMost 叶节点）。

``` c++
TC = O(N)
SC = O(N)

class Solution {
private:
    // 获取前趋节点，即左子树的LeftMost叶节点
    TreeNode* getPrec(TreeNode* root) {
        TreeNode* prec = root->left;
        while (prec->right) {
            prec = prec->right;
        }
        return prec;
    }
public:
    TreeNode* increasingBST(TreeNode* root) {
        if (!root)
            return root;        
        // 若存在左子树
        if (root->left) {
            // 找到前趋节点 P
            TreeNode* prec = getPrec(root);
            // 前趋节点 右连 根节点
            prec->right = root;

            TreeNode* left = root->left;
            // 断开根节点的左指针
            root->left = nullptr;
            // 递归调用左子树
            return increasingBST(left);
        }
        // 若存在右子树
        // 值得注意的是，运行到此处时根节点的左子树已经展平
        // 即是在再次递归调用到根节点时才会真正开始展平右节点
        if (root->right) {
            root->right = increasingBST(root->right); // M
        }
        
        return root;
    }
};****

```

对于根节点来说，分别展平左右子树为链表，使得左子树右连根节点，根节点右连右子树，返回值为左子树的LeftMost叶节点。

以上是我自己实现的Morris遍历变种，深入运行过程，会发现两个问题：

1. 递归调用栈为O(N)，究其原因是左子树内部递归调用时，最后会在 **M** 行处的递归调用形成整个左子树链表的调用栈，接着递归调用在最开始右连上的根节点，继而递归调用右子树，同样也会展平后递归调用，导致整个调用栈为 O(N)
2. Morris遍历需要的获取前趋节点函数与后续递归函数调用有重复访问左树节点的情况

为此，可以把寻找前驱节点的过程和重新连接的过程合并，来自[lee215的解答](https://leetcode.com/problems/increasing-order-search-tree/discuss/165885/C%2B%2BJavaPython-Self-Explained-5-line-O(N))

``` c++
TC = O(N)
SC = O(H)

class Solution {
public:
    // 添加了一个有默认值参数 succ
    TreeNode* increasingBST(TreeNode* root, TreeNode* succ = nullptr) {
        /*
        遍历到空节点，返回的是 succ，中序遍历中的后继节点
        如果 node 是左节点，succ 是其父节点
        如果 node 是右节点，succ 是该路径上 RightMost 父节点的 父节点
                3
              /  \
            1     n4
          /  \
        n1    2
             / \
           n2  n3
        即 n1 返回 1，n3 返回 3
        */
        if (!root) return succ;
        // 递归调用左子树，此时 succ 为左子树的父节点即 root
        TreeNode* res = increasingBST(root->left, root);
        // 断开 root 的左指针
        // 此时在左子树的递归调用中已经完成了左子树 RightMost 节点右接 root
        root->left = NULL;
        // 递归调用右子树，右子树的返回值为 succ
        // 注意，在上述以 2 为父的树中，右空节点递归调用的 succ = 3 为返回值
        // 2->right = call(n3, 3) = 3
        // 该递归调用来自于以 1 为父的树中 call(2, 3) = 2
        root->right = increasingBST(root->right, succ);
        // 左子树返回值为当前root下的LeftMost节点
        return res;
    }
};
```

### 2. 正常做法

一般的递归或迭代方法也能完成

使用一个节点记录LeftMost节点，用额外节点按照中序遍历

``` c++
TC = O(N)
SC = O(H)

class Solution {
public:
    // 返回值，LeftMost节点
    TreeNode* res = nullptr;
    // 当前节点
    TreeNode* cur = nullptr;
    TreeNode* increasingBST(TreeNode* root) {
        if(!root)
            return root;
        inorder(root);
        return res;
    }
    
    void inorder(TreeNode* root) {
        if(!root)
            return;
        // 中序遍历
        inorder(root->left);
        if (!res) {
            // 找到LeftMost节点，记录
            res = root;
            cur = res;
        }
        else {
            // 对于其他节点，安全断开左指针
            root->left = nullptr;
            // 用当前节点右连，并右进
            cur->right = root;
            cur = cur->right;
        }
        // 中序遍历
        inorder(root->right);
        
    }
};
```

``` c++
TC = O(N)
SC = O(H)

class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        if(!root)
            return root;
        
        TreeNode* res, *tmp;
        // 父节点栈
        stack<TreeNode*> st;
        // 当前访问节点
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            // 真正当前访问节点
            cur=st.top();
            st.pop();
            
            if (!res) {
                // 找到LeftMost节点，记录
                res = cur;
                tmp = res;
            }
            else {
                // 对于其他节点，安全断开左指针
                cur->left = nullptr;
                // 用当前节点右连，并前进
                tmp->right = cur;
                tmp = tmp->right;
            }
            // 迭代访问右子树，若不存在会在重新进入 while 时被栈顶替代
            cur = cur->right;
        }
        
        return res;
    }
};
```