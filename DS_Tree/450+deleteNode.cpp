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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->left == NULL) return root->right;
            else if (root->right == NULL) return root->left;
            else { 
                TreeNode* cur = root->right;
                while (cur->left != nullptr) { //找右子树的最左节点
                    cur = cur->left;
                }
                cur->left = root->left;
                TreeNode* tmp = root;
                root = root->right;
                delete(tmp);

                return root;
            }
        }

        TreeNode* tmp = new TreeNode(NULL);
        if (root->val > key) root->left = deleteNode(root->left, key);
        else root->right = deleteNode(root->right, key);

        return root;
    }
 
};