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
private:
    ListNode* mHead;

public:
    Solution(ListNode* head) {
        this->mHead = head;
    }
    
    int getRandom() {
        int i = 1, ans = 0;
        for (auto node = this->mHead; node != nullptr; node = node->next) {
            if (rand() % i == 0) {   // 1/i 的概率选中（替换为答案）
                ans = node->val;
            }
            ++i;
        }
        return ans;
    }   
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */