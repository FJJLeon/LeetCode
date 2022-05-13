# 116. Populating Next Right Pointers in Each Node

## 题目

题面：https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

完全二叉树，每个节点添加一个 next 指针，使得每个指针指向当前层右侧的节点。

``` 
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
};
```

## 思路与实现

类似层序（levelOrder）遍历，填充 next 指针。

### 1. 层序遍历

队列保存 **<Node\*, level>** 对

``` c++
TC=O(N)
SC=O(N)，最后一层队列需要保存N/2的个节点

class Solution {
public:
    Node* connect(Node* root) {
        // <节点，level>
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        while (!q.empty()) {、
            // 当前节点，当前层级
            auto [cur, curL] = q.front(); q.pop();
            if (!cur)
                continue;
            // 当前节点层级 与 队列下一节点同层，则填充 next 指针
            // 防止某层最后一节点 next 连接到下一层 left-most 节点
            if (!q.empty() && q.front().second == curL)
                cur->next = q.front().first;
            // 层序遍历，左右节点入队
            q.push({cur->left, curL + 1});
            q.push({cur->right, curL + 1});
        }
        
        return root;
    }
};
```
队列只保存节点，同层遍历时先保存size
``` c++
class Solution {
public:
    Node* connect(Node* root) {
        if (!root)
            return root;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            // 遍历当前层
            for (int i = q.size(); i > 0; i--) {
                Node* cur = q.front(); q.pop();
                // 当前节点不是所在层最后一个，则给 next 赋值
                if (i > 1)
                    cur->next = q.front();
                // 左右儿子入队
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }
        
        return root;
    }
};
```

### 2. 利用父层 next 指针

利用父层已填充的 next 指针，遍历父层链表，用于子层的 next 指针填充。

迭代实现

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    Node* connect(Node* root) {
        // leftmost 为父层左侧第一个节点
        Node* leftmost = root, *cur;
        // 当某层及下层存在，进行遍历
        while (leftmost && leftmost->left) {
            // cur 为同层遍历的前进节点
            cur = leftmost;
            // 同层横向遍历
            while (cur) {
                // 连接同一个父节点的左右节点
                cur->left->next = cur->right;
                // 连接当前节点的右节点 -> 当前节点的 next 节点的左节点
                if (cur->next)
                    cur->right->next = cur->next->left;
                // 当前节点前进
                cur = cur->next;
            }
            // 纵向，leftmost 节点前进到 leftmost 的左节点
            // 由于是完全二叉树才能这样做
            leftmost = leftmost->left;
        }
        return root;
    }
};
```

递归实现

``` c++
TC=O(N)
SC=O(H)

class Solution {
public:
    Node* connect(Node* root) {
        if (!root)
            return root;
        if (root->left) {
            // 连接同一个父节点的左右节点
            root->left->next = root->right;
            if (root->next)
                // 连接当前节点的右节点 -> 当前节点的 next 节点的左节点
                root->right->next = root->next->left;
        }
        // 递归连接
        connect(root->left);
        connect(root->right);
        return root;
    }
};
```