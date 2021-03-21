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
    int getHeight(TreeNode* node) {
        if (node == NULL) return 0;

        int lheight = getHeight(node->left);
        if (lheight == -1) return -1;
        int rheight = getHeight(node->right);
        if (rheight == -1) return -1;

        if (abs(lheight - rheight) > 1) return -1;

        return 1 + max(lheight, rheight);
    }
    
    bool isBalanced(TreeNode* root) {
        return getHeight(root)==-1 ? false : true;
    }
};