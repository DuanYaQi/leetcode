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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);

        while (!que.empty()) {
            int size = que.size();
            int flag = INT_MIN;

            for (int i = 0; i < size; ++i) {
                TreeNode* node = que.front();
                que.pop();
                flag = node->val > flag ? node->val : flag;
                if (node->left)     que.push(node->left);
                if (node->right)    que.push(node->right);
            }
            res.push_back(flag);
        }
        return res;
    }
};