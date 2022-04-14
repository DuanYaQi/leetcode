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
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;

        ListNode* curr = head;

        while (curr != nullptr) {
            res.push_back(curr->val);
            curr = curr->next;
        }
        reverse(res.begin(), res.end());

        return res;
    }
};