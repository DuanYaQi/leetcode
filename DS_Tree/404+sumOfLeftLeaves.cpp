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
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == NULL) return 0;

        int leftnum = sumOfLeftLeaves(root->left);
        int rightnum = sumOfLeftLeaves(root->right);

        int midnum = 0;
        if (root->left && !root->left->left && !root->left->right) {
            midnum = root->left->val;
        }

        return midnum + leftnum + rightnum;
    }
};