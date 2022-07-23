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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildAVL(vector<ListNode*> &vecs, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + end >> 1;
        TreeNode* root = new TreeNode(vecs[mid]->val);
        root->left = buildAVL(vecs, start, mid - 1);
        root->right = buildAVL(vecs, mid + 1, end);
        return root;    
    }

    TreeNode* sortedListToBST(ListNode* head) {
        vector<ListNode*> vecs;

        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            vecs.push_back(cur);
        }

        TreeNode* root = buildAVL(vecs, 0, vecs.size() - 1);

        return root;
    }
};