#include"util/list.cpp"

/**
 * two itearator alternately link
 * 
 * Runtime: 8 ms, faster than 99.87%, O(N)
 * Memory Usage: 9.8 MB, less than 28.57%, O(1)
*/
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next)
            return head;
        // odd and even itearator
        ListNode *odd = head, *even = head->next;
        // store even list head
        ListNode *even_head = even;
        while (odd->next && even->next) {
            // link odd node
            odd->next = even->next;
            odd = odd->next;
            // link even node
            even->next = odd->next;
            even = even->next;
        }
        // link odd list tail with even list head
        odd->next = even_head;
        return head;
    }
};
