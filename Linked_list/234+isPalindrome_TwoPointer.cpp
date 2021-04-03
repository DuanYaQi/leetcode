/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vc;

        while (head != nullptr) {
            vc.push_back(head->val);
            head = head->next;
        }

        for (int i = 0, j = vc.size() - 1; i < j; ++i, --j) {
            if (vc[i] != vc[j]) {
                return false;
            }
        }
        return true;
    }
};