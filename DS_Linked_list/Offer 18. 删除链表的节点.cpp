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
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* curr = head;
        ListNode* res = new ListNode(0);
        res->next = head;
        ListNode* prev = res;

        while (curr != nullptr) {
            if (curr->val == val) {
                prev->next = curr->next;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        return res->next;
    }
};