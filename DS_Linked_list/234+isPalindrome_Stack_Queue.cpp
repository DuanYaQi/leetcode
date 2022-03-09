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
        stack<int> st;
        queue<int> qu;

        while (head != nullptr) {
            st.push(head->val);
            qu.push(head->val);
            head = head->next;
        }
        
        while (!st.empty()) {
            if (st.top() != qu.front()) {
                return false;
            }
            st.pop();
            qu.pop();
        }

        return true;
    }
};