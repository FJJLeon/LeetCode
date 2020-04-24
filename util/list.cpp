#include<stddef.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Definition for doubly-linked list.
struct DoublyNode {
    int val;
    DoublyNode *next;
    DoublyNode *last;
    DoublyNode(int x) : val(x), next(NULL), last(NULL) {}
    //DoublyNode(int x, DNode *n, DNode *l) : val(x), next(n), last(l) {}
};
