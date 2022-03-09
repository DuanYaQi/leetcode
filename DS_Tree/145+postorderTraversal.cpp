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
private:
    vector<int> res;
public:
    void traversal (TreeNode* root) {
        if (!root) return;
        traversal(root->left);
        traversal(root->right);
        res.push_back(root->val);
        return;
    }
    vector<int> postorderTraversal(TreeNode* root) {
        traversal(root);
        return res;
    }
};