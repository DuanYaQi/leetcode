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
    unordered_map<string, int> ump;
    vector<TreeNode*> res;

    string dfs(TreeNode* root) {
        if (root == nullptr) return "";

        string tmp = to_string(root->val) + "," + dfs(root->left) + "," + dfs(root->right);

        if (ump[tmp] == 1)
            res.push_back(root);


        ump[tmp]++;

        return tmp;
    }


    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);

        return res;
    }   
};