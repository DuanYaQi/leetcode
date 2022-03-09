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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if(root == NULL) return res;
        tmp.push_back(root->val);
        traversal(root, targetSum, root->val);
        return res;
    }

private:
    vector<vector<int>> res;
    vector<int> tmp;
    void traversal(TreeNode* root, int targetSum, int count) {
        if (!root->left && !root->right && count == targetSum) {
            res.push_back(tmp);
            return;
        }
        
        if (!root->left && !root->right) {
            return;
        }

        if (root->left) {
            tmp.push_back(root->left->val);
            traversal(root->left, targetSum, count + root->left->val);
            tmp.pop_back();
        }

        if (root->right) {
            tmp.push_back(root->right->val);
            traversal(root->right, targetSum, count + root->right->val);
            tmp.pop_back();
        }

        return;
    }
};