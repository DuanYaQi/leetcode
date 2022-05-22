/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p->right != nullptr) {
            TreeNode* node = p->right;

            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }
        
        
        TreeNode* ans = nullptr;
        TreeNode* node = root;
        while (node != nullptr) {
            if (node->val > p->val) {
                ans = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return ans;
    }
};