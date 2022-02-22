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
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        while (!que.empty()){
            int size = que.size();
            TreeNode* node;

            for (int i = 0; i < size; ++i) {
                node = que.front();
                que.pop();

                if (node->left != nullptr) que.push(node->left);
                if (node->right != nullptr) que.push(node->right);
                swap(node->left, node->right);
            }
       }
       return root;
    }
};