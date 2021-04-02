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
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr){
            return NULL;
        }
        /**
         * 下列操作会超出时间限制    原因是这样写的起点是虚拟头节点dummy_head  因为fast一次走两格，如果他从head走，是不会走到head->next的位置的,只能走到 head->next->next 所以相遇后找入口从head出发的cur是碰不到slow的
         
         
        但是在141是正确的，因为是可以相遇的
        
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        
         * ***/
        ListNode* fast = head->next->next;
        ListNode* slow = head->next;

        while (fast != NULL && fast->next != NULL) {
            if (slow == fast) {
                ListNode* cur = head;
                while (cur != slow) {
                    slow = slow->next;
                    cur = cur->next;
                }
                return cur;
            }
            
            slow = slow->next;
            fast = fast->next->next;
        }

        return NULL;
    }
};