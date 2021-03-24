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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty()) return nullptr;

        int index = 0;
        int maxv = INT_MIN;
        for(int i = 0; i < nums.size(); ++i) {
            if (nums[i] > maxv) {
                maxv = nums[i];
                index = i;
            }
        }

        vector<int> numsl(nums.begin(), nums.begin() + index);
        vector<int> numsr(nums.begin() + index + 1, nums.end());

        TreeNode* root = new TreeNode(maxv);
        root->left = constructMaximumBinaryTree(numsl);
        root->right = constructMaximumBinaryTree(numsr);
        return root;
    }
};