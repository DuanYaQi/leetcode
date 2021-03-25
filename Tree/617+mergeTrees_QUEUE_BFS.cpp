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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL) return root2;
        if (root2 == NULL) return root1;

        queue<TreeNode*> que1;
        queue<TreeNode*> que2;

        que1.push(root1);
        que2.push(root2);
        

        while (!que1.empty() && !que2.empty()) {
            TreeNode* node1 = que1.front();
            que1.pop();
            TreeNode* node2 = que2.front();
            que2.pop();
            
            node1->val += node2->val;

            if (node1->left && node2->left) {
                que1.push(node1->left);
                que2.push(node2->left);
            } 

            if (node1->right && node2->right) {
                que1.push(node1->right);
                que2.push(node2->right);
            }

            if (!node1->left && node2->left) {
                node1->left = node2->left;
            }

            if (!node1->right && node2->right) {
                node1->right = node2->right;
            } 
        }

        return root1;
    }
};