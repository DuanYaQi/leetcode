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
    bool traversal(TreeNode* root, int targetSum, int count) {
        if (!root->left && !root->right && count == targetSum) {    //遇到叶子结点且值相同,即找到路径 直接返回true
            return true;
        }

        if (!root->left && !root->right) {      //遇到叶子结点但值不同,没有找到路径 返回false
            return false;
        }

        if (root->left) {       // 处理左节点
            if (traversal(root->left, targetSum, count + root->left->val)) return true;
        }

        if (root->right) {      // 处理右节点
            if (traversal(root->right, targetSum, count + root->right->val)) return true;
        }

        return false;
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return false;
        return traversal(root, targetSum, root->val);
    }
};