# 236. Lowest Common Ancestor of a Binary Tree

## 题目

题面：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/

找到二叉树两个节点的的最近公共祖先 LCA。

## 实现


### 1. 递归 DFS

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

上述实现中使用了一个全局变量，且需要用额外成员函数。

对这个搜索过程进行思考，其实可以进行进一步简化实现，不适用额外变量也不需要额外函数。

* 首先 p 和 q 一定是以 root 为根的树的子节点。若发现 root 是 p 或者 q 中一个，那么 root 必然是 p 和 q 的 LCA，直接返回 root 节点
* 若不然，对左右子树递归调用，分别返回 l 和 r，若我们发现其中一个是空值，那么可以知道 p 和 q 均在另一子树中，直接返回非空值
  * 可能会问，这样返回的非空值是最深的祖先节点吗？是的，会发现LCA的祖先节点的递归调用的返回值同样是 LCA
* 若发现 l 和 r 都不为空，那么 p 和 q 分别在两个子树中，返回 root 节点便是 LCA
* 对 root 来说，不存在 l 和 r 都为空的情况
``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root)
            return root;
        if (root == p || root == q)
            return root;
        
        TreeNode *l = lowestCommonAncestor(root->left, p, q), 
                 *r = lowestCommonAncestor(root->right, p, q);
        if (l && r)
            return root;
        
        return l ? l : r;
    }
};
```

### 2. 迭代实现

迭代实现可以用一个字典在迭代DFS的过程维护每个节点的父节点，完成后从 p 节点自底向上用一个集合记录 p 到 root 路径上的节点，接着再从 q 节点自底向上访问路径节点，一旦发现第一个与集合中的节点相交，则为 LCA。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> st;
        map<TreeNode*, TreeNode*> parent;
        
        st.push(root);
        parent.insert({root, NULL});
        // 迭代 DFS 过程维护 parent 字典，直到 p、q 都在字典中
        while (parent.find(p) == parent.end() || parent.find(q) == parent.end()) {
            TreeNode* node = st.top(); st.pop();
            if (node->left) {
                parent.insert({node->left, node});
                st.push(node->left);
            }
            if (node->right) {
                parent.insert({node->right, node});
                st.push(node->right);
            }
        }
        // 从 p 节点自底向上用一个集合记录 p 到 root 路径上的节点
        set<TreeNode*> path;
        while (p) {
            path.insert(p);
            p = parent[p];
        }
        // 从 q 节点自底向上访问路径节点，发现有第一个相交即停止
        while (path.find(q) == path.end())
            q = parent[q];
        
        return q;
    }
};
```
