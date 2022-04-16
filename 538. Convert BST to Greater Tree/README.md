# 538. Convert BST to Greater Tree

## 描述

题面：https://leetcode.com/problems/convert-bst-to-greater-tree/

给定一棵BST，让每个节点值都累加上比该节点大的数值和，即把（在BST中序遍历中）在节点右侧的节点值求和加到当前节点。

## 思路与实现

由于是一棵BST，反向中序（右中左）遍历，过程中记录累加值

### 1. 递归

反向中序遍历的递归实现

``` c++

TC = O(N)
SC = O(H)，递归栈空间，与树高H呈正比，最差情况为O(N)

class Solution {
public:
    // 全局变量记录累加值
    int sum = 0;
    
    TreeNode* convertBST(TreeNode* root) {
        if (!root)
            return root;
        // 遍历右子树
        convertBST(root->right);
        // 处理当前节点，累加 sum
        sum += root->val;
        root->val = sum;
        // 遍历左子树
        convertBST(root->left);
        
        return root;
    }
};

```

其实使用全局变量不太好，此处也可定义函数，通过引用传递记录累加值

``` c++
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        helper(root, sum);
        return root;
    }
    // 引用传递记录累加值
    void helper(TreeNode* node, int& sum) {
        if (!node)
            return;
        helper(node->right, sum);
        node->val += sum;
        sum = node->val;
        helper(node->left, sum);
    }
};
```

### 2. 迭代

通过栈实现反向中序遍历

``` c++

TC = O(N)
SC = O(H)

class Solution {
public:    
    TreeNode* convertBST(TreeNode* root) {      
        stack<TreeNode*> st;
        TreeNode* node = root;
        
        int sum = 0;
        while (!st.empty() || node) {
            // 迭代到 RightMost 节点
            while (node) {
                st.push(node);
                node = node->right;
            }
            // 取出还未被遍历过的 RightMost 节点
            node = st.top(); st.pop();
            // 处理 RightMost 节点
            sum += node->val;
            node->val = sum;
            // 若 RightMost 节点存在左子树，则会在下次 While 循环进行遍历
            // 否则会回去取出 RightMost 节点的父节点
            node = node->left;
        }
        
        return root;
    }
};
```

### Morris 遍历

不使用额外空间进行反向中序遍历

核心思想是在遍历过程中，对于每个存在右子树的节点，利用后继叶子节点的空闲左指针，使之临时指向当前节点，从而在遍历右子树时无需记录该父节点。

为便于未来理解，这里需要注意的是：
1. 存在右子树的节点 P，才需要进行右子树的遍历，此时不能直接处理 P
2. 后继叶子节点 S 指在BST中序遍历中，当前节点 P 的下一个节点，即这是右子树中值最接近（大于）当前节点值的
3. 后继叶子节点 S 左指针指向当前节点 P，那么在右子树遍历到最后，即遍历到 S 时，按照右左中的反向中序遍历顺序，会继而遍历回到 P
4. 当然，在 P 的本次遍历中，会发现后继叶子节点 S 左指针已经指向了自己，意味着此时是真正需要处理 P 了，在处理之前，需要断开临时指针连接

``` c++
TC = O(N)
SC = O(1)

class Solution {
public:    
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        TreeNode* node = root;
        
        while (node) {
            // 处理不存在右子树的节点
            if (!node->right) {
                sum += node->val;
                node->val = sum;
                node = node->left;
            }
            // 处理存在右子树的节点
            else {
                // 找到后继叶子节点 succ
                TreeNode* succ = getSucc(node);
                // 若 succ 没有 left 指针，意味着右子树还未遍历
                if (!succ->left) {
                    // 使得 succ 的左指针临时连接到当前节点
                    succ->left = node;
                    node = node->right;
                }
                // 若 succ 存在 left 指针，意味着右子树已经遍历
                // 该 left 指针必然等于当前节点 node
                else {
                    // 断开临时指针连接
                    succ->left = nullptr;
                    // 真正处理存在右子树的节点
                    sum += node->val;
                    node->val = sum;
                    node = node->left;
                }
            }
        }
        
        return root;
    }
    // 找到 node 的后继叶子节点
    TreeNode* getSucc(TreeNode* node) {
        TreeNode* succ = node->right;
        // 走右子树的 LeftMost 路径，
        // 可能已经临时连接，故不能等于 node 本身
        while (succ->left && succ->left != node) {
            succ = succ->left;
        }
        return succ;
    }
};

```