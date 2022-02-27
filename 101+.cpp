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
    vector<int> dfs(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        vector<int> vec;

        while (!que.empty()) {
            int size = que.size();
            TreeNode* node;

            for (int i = 0; i < size; ++i) {
                node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left != nullptr) que.push(node->left);
                if (node->right != nullptr) que.push(node->right);
            }    
        }
        return vec;      
    }
    
    bool isSymmetric(TreeNode* root) {
       if (root == nullptr) return true;
       TreeNode* nodeL = root->left;
       TreeNode* nodeR = root->right;
       if (nodeL == nullptr & nodeR == nullptr) return true;
       if ( (nodeL == nullptr & nodeR != nullptr) || (nodeL != nullptr & nodeR == nullptr)) return false;
       vector<int> f1 = dfs(nodeL);
       vector<int> f2 = dfs(nodeR);
       
       if (f1 == f2) {
           return true;
       } else {
           return false;
       }
    }
};