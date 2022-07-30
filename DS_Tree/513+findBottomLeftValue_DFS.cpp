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
    void dfs(TreeNode* root, int level) {
        if (root->left != nullptr) dfs(root->left, level + 1);
        if (root->right != nullptr) dfs(root->right, level + 1);
        
        if (maxlevel < level) {
            maxlevel = level;
            res = root->val;
            return;
        }

        return;
    }

    int findBottomLeftValue(TreeNode* root) {
        maxlevel = -1;
        dfs(root, 0);
        return res;
    }

private:
    int res;
    int maxlevel;
};