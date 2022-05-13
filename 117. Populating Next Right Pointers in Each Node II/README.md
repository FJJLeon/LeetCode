# 117. Populating Next Right Pointers in Each Node II

## 题目

题面：https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

二叉树，每个节点添加一个 next 指针，使得每个指针指向当前层右侧的节点。

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

本题二叉树访问顺序类似层序（levelOrder）遍历，在过程中构建 next 指针。

### 1. 基于Queue的层序遍历

二叉树一般基于Queue进行层序遍历，在遍历一层节点时，将所有子节点入队，按层遍历

``` c++
TC=O(N)
SC=O(N)，队列存储某层节点

class Solution {
public:
    Node* connect(Node* root) {
        if (!root)
            return root;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            // 遍历当前层
            // 注意不能用 (i=0; i<q.size(); i++) 进行循环，在遍历中会有入队
            for (int i = q.size(); i > 0; i--) {
                Node* cur = q.front(); q.pop();
                // 当前节点不是所在层最后一个，则给 next 赋值
                if (i > 1) {
                    cur->next = q.front();
                }
                // 层序遍历，若存在则将左右子节点入队
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

### 2. 利用父层 next 指针和冗余节点

在层序遍历过程中，其实构建完了的一层节点可以利用 next 指针类似链表进行横向遍历，用于下一层的next构建。

并利用一个冗余节点保存每层的第一个节点，否则就可能要设置一个是否开始某层构建的 flag。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    Node* connect(Node* root) {
        // 冗余节点，用于指向每个子层构建时的 left-most 节点
        Node* dummy = new Node(0);
        // cur 是父层next链表遍历指针
        // needle 是子层构建时的前进指针，初始为 dummy
        Node *cur = root, *needle = dummy;
        while (cur) {
            // 1. 每个父层的横向遍历
            while (cur) {
                // 1.1. 子层 next 指针构建
                // 若存在左儿子，needle 构建 next 并前进
                if (cur->left) {
                    needle->next = cur->left;
                    needle = needle->next;
                }
                // 若存在右儿子，needle 构建 next 并前进
                if (cur->right) {
                    needle->next = cur->right;
                    needle = needle->next;
                }
                // 1.2 父层横向遍历前进
                cur = cur->next;
            }
            // 2. 纵向，进入下一层遍历，将下一层作为父层构建下下层 next 指针
            // 冗余节点的 next 是下一层的 left-most
            cur = dummy->next;
            // 冗余节点 next 指针置空，否则会进入无限循环
            dummy->next = nullptr;
            // 重置 needle 构建指针
            needle = dummy;
        }
        delete dummy;
        return root;
    }
};
```
