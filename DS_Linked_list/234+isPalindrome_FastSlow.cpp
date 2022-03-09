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
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next !=nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode* reverseLL = reverseLinklist(slow);

        ListNode* cur = head;
        while (reverseLL != nullptr) {
            if (reverseLL->val != cur->val) {
                return false;
            }
            cur = cur->next;
            reverseLL = reverseLL->next;
        }

        return true;
    }

private:
    ListNode* reverseLinklist(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* tmp;
        ListNode* cur = head;

        while (cur != nullptr) {
            tmp = pre;
            pre = cur;
            cur = cur->next;
            pre->next = tmp;
        }

        return pre;
    }

};