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
    void dfs(TreeNode* root, vector<int> &res) {
        if (root == nullptr) return;

        dfs(root->left, res);
        res.push_back(root->val);
        dfs(root->right, res);
    }

    int kthSmallest(TreeNode* root, int k) {
        vector<int> res;
        dfs(root, res);

        return res[k-1];
    }
};