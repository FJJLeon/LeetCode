# [234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)

## 题目

判断链表是否是回文

## 实现

不同于数组可以按索引随机访问，链表无法随机访问，导致了访问判断回文所需节点的困难。如果暴力成对访问，每次都从头节点访问 i 和 N-i 次，则时间复杂度为 O(N^2)。

### 1. 利用栈

如何解决上述访问节点顺序的问题呢？一个利用额外空间的做法是用栈来保存前半部分的节点，对于后半部分和栈中节点成对比较。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 计算链表长度
        ListNode* cur = head;
        int n = 0;
        while (cur) {
            cur = cur->next;
            n++;
        }
        // 将前半链表入栈
        stack<int> st;
        cur = head;
        int c = 0;
        while (c < n / 2) {
            st.push(cur->val);
            cur = cur->next;
            c++;
        }
        // 如果长度为奇数，则跳过中间节点
        if (n & 1)
            cur = cur->next;
        // 将后半链表和栈进行成对比较
        while (cur) {
            if (cur->val != st.top())
                return false;
            cur = cur->next;
            st.pop();
        }
        return true;
    }
};
```

利用快慢指针可以避免最开始的节点计数。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 快慢指针
        ListNode* fast = head, *slow = head;
        stack<int> st;
        while (fast && fast->next) {
            // 快指针前进两步
            fast = fast->next->next;
            // 慢指针前进一步，同时入栈
            st.push(slow->val);
            slow = slow->next;
        }
        // 如果快指针不为空，则链表为奇数，慢指针跳过中间节点到达后半链表的开始节点
        if (fast) {
            slow = slow->next;
        }

        while (slow) {
            if (slow->val != st.top())
                return false;
            slow = slow->next;
            st.pop();
        }
        return true;
    }
};
```

### 2. 翻转半链表

能否不适用额外空间，这样就需要对前半或者后半部分链表进行翻转，然后进行比较。一个问题是翻转链表破坏了输入链表的结构，最好能在完成后进行复原。

首先是进行计数的实现

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 节点计数
        int n = 0;
        ListNode* cur = head;
        while (cur) {
            cur = cur->next;
            n++;
        }
        // 找到中间节点（奇数时为中间节点，偶数时为后半链表的开始）
        ListNode* mid = head;
        for (int i = 0; i < n / 2; i++) {
            mid = mid->next;
        }
        // 若节点数为奇数，则中间节点后移一步，此时 mid 为后半链表的开始
        if (n & 1)
            mid = mid->next;
        // 翻转后半链表
        mid = reverse(mid);
        cur = head;
        // 比较前半链表和翻转后的后半链表
        for (int i = 0; i < n / 2; i++, cur = cur->next, mid = mid->next) {
            if (cur->val != mid->val)
                return false;
        }
        return true;
    }
    // 翻转链表
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode* rev = nullptr;
        // 对于每个节点，实现同时的 (rev, rev->next, head) = (head, rev, head->next)
        while (head) {
            // 两种实现，都是用临时变量打破依赖
/*
            // tmp 记录上次的 rev节点，临时记录，打破依赖
            ListNode* tmp = rev;
            // rev 赋值为当前 head 节点
            rev = head;
            // head 节点前进，准备下次翻转，必须在下一步之前，否则链表的下一个节点将无法访问到
            head = head->next;
            // 新的头节点 next 指向 tmp 即未翻转的 head 节点
            rev->next = tmp;
*/
            // tmp 记录当前 head 节点，临时记录，打破依赖
            ListNode* tmp = head;
            // haed 节点前进，准备下次翻转
            head = head->next;
            // tmp 即未翻转的 head 节点的 next 指向 rev
            tmp->next = rev;
            // rev 赋值为 tmp，当前已翻转的最后一个节点，最后作为新的头节点
            rev = tmp;
            
        }
        return rev;
    }
};
```

同样利用快慢指针实现

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 快慢指针
        ListNode *fast = head, *slow = head, *mid;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        // 若奇数，跳过中间节点
        if (fast)
            slow = slow->next;
        // 翻转后半链表
        slow = reverse(slow);
        // 比较前半链表和翻转后的后半链表
        while (slow && head) {
            if (slow->val != head->val)
                return false;
            slow = slow->next;
            head = head->next;
        }
        return slow == nullptr;
    }
    
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode* rev = nullptr;
        while (head) {
            // ListNode* tmp = rev;
            // rev = head;
            // head = head->next;
            // rev->next = tmp;
            ListNode* tmp = head;
            head = head->next;
            tmp->next = rev;
            rev = tmp;
            
        }
        return rev;
    }
};
```

另外，实际上快慢指针确定中间节点和翻转链表的过程可以一起做，利用 slow 翻转前半部分链表

``` c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *fast = head, *slow = head, *rev = nullptr;
        while (fast && fast->next) {
            // 快指针前进两步
            fast = fast->next->next;
            // 慢指针前进一步，同时利用 rev 进行翻转
            ListNode* tmp = rev;
            rev = slow;
            slow = slow->next;
            rev->next = tmp;
            
            // ListNode* tmp = slow;
            // slow = slow->next;
            // tmp->next = rev;
            // rev = tmp;
        }
        // 若奇数，跳过中间节点
        if (fast)
            slow = slow->next;
        // 比较翻转的前半部分链表和未翻转的后半部分链表
        while (rev && slow) {
            if (rev->val != slow->val)
                return false;
            rev = rev->next;
            slow = slow->next;
        }
        return true;
    }
};
```
