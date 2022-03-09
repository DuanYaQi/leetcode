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
    int tmp = 0;
    void traversal(TreeNode* root) {
        if (root == nullptr) return;
        traversal(root->right);
        root->val = root->val + tmp;
        tmp = root->val;
        traversal(root->left);
        return;
    }
    
    TreeNode* convertBST(TreeNode* root) {
        traversal(root);
        return root;
    }
};