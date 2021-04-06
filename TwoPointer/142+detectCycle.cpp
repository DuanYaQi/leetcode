/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) {
            return NULL;
        }
        ListNode* cur = head;
        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        
        while (slow != fast && fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        if(fast == NULL || fast->next == NULL) {
            return NULL;
        }

        while (cur != slow) {
            cur = cur->next;
            slow = slow->next;
        }
        return slow;
    }
};