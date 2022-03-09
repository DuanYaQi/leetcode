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
    TreeNode* getBST(vector<int>& nums, int start, int end) {
        if (start > end) return nullptr;
        int index = start + (end - start) / 2;
        TreeNode* root = new TreeNode(nums[index]);
        root->left = getBST(nums, start, index - 1);
        root->right = getBST(nums, index + 1, end);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        TreeNode* root;
        root = getBST(nums, 0, nums.size() - 1);
        return root;
    }
};