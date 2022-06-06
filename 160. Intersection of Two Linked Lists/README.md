# 160. Intersection of Two Linked Lists

## 题目

题面：https://leetcode.com/problems/intersection-of-two-linked-lists/

两个链表，找到相交的节点

## 实现

### 1. 哈希集合


### 2. 快慢指针

headA 前进到末尾，将末尾连接到 headB 头。此时问题转换为 headA 链表是否有环，若有则找到环的入口，即 [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) 的解法。

``` c++
TC=O(M+N)
SC=O(1)

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // curA 前进到末尾，将末尾连接到 headB 头
        ListNode* curA = headA;
        while (curA->next)
            curA = curA->next;
        curA->next = headB;
        // 判断是否有环
        ListNode* slow = headA, *fast = headA;
        while (slow != NULL && fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }
        // 没有环，则返回 NULL
        if (fast == NULL || fast->next == NULL) {
            // 断开连接
            curA->next = NULL;
            return NULL;
        }
        // 有环，找到环的入口
        slow = headA;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        // 断开连接
        curA->next = NULL;
        return slow;
    }
};
```

看题解，发现双指针的解法实际上可以非常优雅。

设链表 A 的长度为 a+T, 链表 B 的长度为 b+T, 其中 T 是环的长度。从 A 和 B 的头节点开始，每次前进一步，当 A 走到末尾后转而走 B 的头节点，当 B 走到末尾也转走 A 的头节点，两者必会相遇，相遇点要么为环入口，要么就是空指针。

指针 A 走过的节点为 a + T + b，而指针 B 走过的节点为 b + T + a，两者恰好相遇在环入口，若不会相交则相遇在末尾。

``` c++
TC=O(M+N)
SC=O(1)

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA, *curB = headB;
        while (curA != curB) {
            // A 前进，到末尾时转而走 B 的头节点
            curA = curA ? curA->next : headB;
            // B 前进，到末尾时转而走 A 的头节点
            curB = curB ? curB->next : headA;
        }
        return curA;
    }
};
```
