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
    void dps (TreeNode* root, vector<string> &res, string ans) {
        TreeNode* l = root->left;
        TreeNode* r = root->right;

        if (!l && !r) {
            res.push_back(ans); 
            return;
        }   

        if (l!=NULL) {
            dps(l, res, ans + "->" + to_string(l->val));
        }

        if (r!=NULL) {
            dps(r, res, ans + "->" + to_string(r->val));
        }   

        return;
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (root == NULL) return res;
        string ans = to_string(root->val);
        dps(root, res, ans);
        return res;
    }
};