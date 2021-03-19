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
//queue实现
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) {
            que.push(root->left);
            que.push(root->right);
        }

        while (!que.empty()) {
            TreeNode* left = que.front(); que.pop();
            TreeNode* right = que.front(); que.pop();

            if (!left && !right) { //都为空，即对称
                continue;
            }

            // 前边已经排除都为空，下边只能出现只有一个为空，或者值不相同，触发false 
            if ( ( !left || !right || (left->val != right->val) )) {
                return false;
            }

            que.push(left->left);que.push(right->right);
            que.push(left->right);que.push(right->left);
        }
        return true;
    }
};