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
    vector<int> robTree(TreeNode* cur) {
        if (cur == nullptr) return vector<int> {0, 0};

        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);

        int val1Choice = cur->val + left[0] + right[0];
        int val0Choice = max(left[0], left[1]) + max(right[0], right[1]);
        
        return vector<int> {val0Choice, val1Choice};
    }

    int rob(TreeNode* root) {
        vector<int> res = robTree(root);
        return max(res[0], res[1]);
    }
};