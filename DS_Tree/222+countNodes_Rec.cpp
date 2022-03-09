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
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        TreeNode* l = root->left;
        TreeNode* r = root->right;
        int ldepth = 1;
        int rdepth = 1;

        while (l) {
            ++ldepth;
            l = l->left;
        }

        while (r) {
            ++rdepth;
            r = r->right;
        }

        if (ldepth == rdepth) {
            return pow(2, ldepth) - 1;
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};