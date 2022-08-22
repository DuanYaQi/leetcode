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
    void getHeight(TreeNode* root, int curheight) {
        if (root == nullptr) return;
        height = max(height, curheight);

        if (root->left) getHeight(root->left, curheight + 1);
        if (root->right) getHeight(root->right, curheight + 1);
        return;
    }

    void dfs(TreeNode* root, int r, int c, vector<vector<string>> &res) {
        if (root == nullptr) return;
        res[r][c] = to_string(root->val);
        if (root->left) dfs(root->left, r + 1, c - pow(2, height - r - 1), res);
        if (root->right) dfs(root->right, r + 1, c + pow(2, height - r - 1), res);
        return;
    }
    
    vector<vector<string>> printTree(TreeNode* root) {
        getHeight(root, 0);
        int m = height + 1, n = pow(2, height + 1) - 1;
        vector<vector<string>> res(m, vector<string>(n));
        dfs(root, 0, n - 1 >> 1, res);

        
        return res;
    }
private:
    int height;    
};