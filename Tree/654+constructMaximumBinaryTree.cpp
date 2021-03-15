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
    TreeNode* build(vector<int>& nums, int l, int r) {
        if (l > r) return nullptr;

        int index = l;
        for (int i = l; i <= r; i++) { 
            if (nums[i] > nums[index])  index = i;
        }

        TreeNode* root = new TreeNode(nums[index]);

        root->left = build(nums, l, index-1);
        root->right = build(nums, index+1, r);
        return root;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
       return build(nums, 0 ,nums.size()-1);
    }
};