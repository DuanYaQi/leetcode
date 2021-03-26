/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }

private: 
    int result = INT_MAX;
    TreeNode* pre;
    void traversal(TreeNode* root) {
        if (root == NULL) return; 
        traversal(root->left);
        if (pre) {
            result = min(result, root->val - pre->val);
        }
        pre = root;
        traversal(root->right);
        return;
    }
};