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
        if (root == NULL) return 0;
        traversal(root);

        int ans = INT_MAX;
        for (int i = 1; i < res.size(); ++i) {
            ans = res[i] - res[i-1] < ans ? res[i] - res[i-1] : ans;
        }
        return ans;
    }

private: 
    vector<int> res;
    void traversal(TreeNode* root) {
        if (root == NULL) return; 
        traversal(root->left);
        res.push_back(root->val);
        traversal(root->right);
        return;
    }
};