#include<iostream>
using namespace std;

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p1 = l1, *p2 = l2;
        ListNode* dumpyHead = new ListNode(-1);
        ListNode* cur = dumpyHead;
        int carried = 0;

        while(p1 || p2){
            int a = p1? p1->val: 0;
            int b = p2? p2->val: 0;

            cur->next = new ListNode((a + b + carried ) % 10);

            carried = (a + b + carried)/10;
            cur = cur->next;
            p1 = p1? p1->next : NULL;
            p2 = p2? p2->next : NULL;
        }   
        cur->next = carried? new ListNode(1) : NULL;
        ListNode* res = dumpyHead->next;
        delete dumpyHead;
        return res;
    }
};