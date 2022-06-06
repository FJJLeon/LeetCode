# 142. Linked List Cycle II

## 题目

题面：https://leetcode.com/problems/linked-list-cycle-ii/

判断链表是否有环，如果有环，找到环的入口节点，如果没有环，返回null

## 实现

### 1. 哈希集合


### 2. 快慢指针

在 [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) 的基础上，再使用一个新指针从头开始与某个指针同步前进，第二次相遇时即为环的入口节点。

fast、slow 指针从 head 开始，slow 每次前进一步，fast 每次前进两步，如果有环，则快指针会追上慢指针。

考虑有环的情况，设从头到环入口有 a 个节点，环有 T 个节点；快慢指针分别走过 f、s 步，则有：

* fast 走过的节点是 slow 的两倍：f = 2s
* fast 比 slow 多走整倍数环长度：f = s + nT

可得，s = nT, f = 2nT

从头节点走过 a + nT 个节点会循环到达环入口，在上述相遇时刻，再设置一个新指针 res，与 slow 一起前进，恰好会在环入口相遇，此时 res 走过 a 个节点，slow 走过 a + nT 个节点。

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head, *res = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            // slow 与 fast 相遇
            if (slow == fast) {
                // slow 与 res 相遇
                while (slow != res) {
                    slow = slow->next;
                    res = res->next;
                }
                return res;
            }
        }
        return nullptr;
    } 
};
```
