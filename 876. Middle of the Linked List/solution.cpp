#include"util/list.cpp"


/**
 * Fast & Slow pointer
 * slow forward one step while fast forward two step
 * 
 * Runtime: 0 ms, O(N)
 * Memory Usage: 6.3 MB, O(1)
*/
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head, *slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
