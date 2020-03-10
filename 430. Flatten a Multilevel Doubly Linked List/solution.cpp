#include<stack>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

/**
 * my first solution
 * 使用 stack 保存遇到 child 时的 next 节点供压平深层返回时使用
 * comments for detail explain
 * 
 * 该操作的表现：
 * 压平是 DFS 的，在压平每一层的过程中发现新 child，都会优先压平下一层
 * 故最先完成压平的是第一个 child 的最深层
 * 
 * Runtime: 4 ms
 * Memory Usage: 8.9 MB
*/
class Solution1 {
public:
    Node* flatten(Node* head) {
        Node* n = head;
        stack<Node*> levelNext;
        // next null, child null, stack empty --> loop end
        while (n && (n->next || n->child || !levelNext.empty()) ) {
            // child exist, prioritize
            if (n->child) {
                // save next
                levelNext.push(n->next);
                // flatten down
                n->next = n->child;
                n->child->prev = n;
                // remove child
                n->child = NULL;
            } 
            // child not exist, next is null (one level tail)
            // now stack not empty
            else if (!n->next) {
                // pop stack until finding a non-null next
                // or next is "first level tail"
                while (!levelNext.empty() && !levelNext.top())
                    levelNext.pop();
                // find success, flatten up
                if (!levelNext.empty()) {
                    n->next = levelNext.top();
                    n->next->prev = n;
                    levelNext.pop();  
                }
                // find fail, next is "first level tail"
                else {
                    n->next = NULL; 
                }
            }
            // step forward
            n = n->next;
        }
        
        return head;
    }
};

/**
 * 该操作的表现：
 * 发现一层，压平一层，暂时不去考虑压平的层中是否还有 child
 * 压平该层完成后会重新当作上层步进以发现可能存在的 原来更深层的 child level
 * 
 * 违直觉想法，学到了
 * 但是该方法下会对 child level 层的节点重复访问 next
 * 我的方法下每个节点都仅处理一次
 * 
 * Runtime: 4 ms
 * Memory Usage: 8.9 MB
*/
class Solution2 {
public:
    Node* flatten(Node* head) {
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->child) {
                // save current level next node
                Node* up = cur->next;
                // attach cur to child
                cur->next = cur->child;
                cur->next->prev = cur;
                cur->child = NULL;
                // find child level tail
                Node* down = cur->next;
                while (down->next) down = down->next;
                // connect tail to up level next
                down->next = up;
                if (up) up->prev = down;
            }
        }
        return head;
    }
};

/**
 * 递归方法，solution 1 其实是把递归方法迭代化了
 * 
 * 递归操作的表现与 solution 1 相同
*/
class Solution3 {
public:
    Node* flatten(Node* head) {
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->child) {
                // save current level next node
                Node *up = cur->next;
                // recursive flatten for child level head
                cur->child = flatten(cur->child);
                // find child level tail, now deeper level is flattened
                Node *down = cur->child;
                while (down->next) down = down->next;
                // attach cur to child
                cur->next = cur->child;
                cur->next->prev = cur;
                cur->child = NULL;
                // connect tail to up level next
                down->next = up;
                if (up) up->prev = down;
            }
        }
        return head;
    }
};