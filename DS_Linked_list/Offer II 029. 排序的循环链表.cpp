/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (head == nullptr) {          // 针对空列表
            head = new Node(insertVal);    
            head->next = head;
            return head;
        }
        
        Node* now = head->next;
        Node* pre = head;        
        
        bool isDeal = false;
        while (now != head) {
            // 降序的位置
            if (now->val <= insertVal && insertVal <= pre->val) {
                Node* newN = new Node(insertVal);
                now->next = newN;
                newN->next = pre;
                isDeal = true;
            }

            // 升序的位置，即 4 - 6 插入 5
            if (pre->val <= insertVal && insertVal <= now->val) {
                Node* newN = new Node(insertVal);
                pre->next = newN;
                newN->next = now;
                isDeal = true;
            }
            pre = now;
            now = now->next;
        }

        if (!isDeal) {
            Node* newN = new Node(insertVal);
            pre->next = newN;
            newN->next = now;
        }
        
        return head;
    }
};