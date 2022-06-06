# 141. Linked List Cycle

## 题目

题面：https://leetcode.com/problems/linked-list-cycle/

判断一个链表是否成环

## 实现

### 1. 哈希集合

用一个集合，记录每个节点的地址，如果有环，则会有重复

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> nodes;
        while (head) {
            if (nodes.count(head))
                return true;
            nodes.insert(head);
            head = head->next;
        }
        return false;
    }
};
```

### 2. 快慢指针

快慢指针，慢指针一次前进一步，快指针一次前进两步，如果有环，则快指针会追上慢指针

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};
```
