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
    vector<int> findMode(TreeNode* root) {
        traversal(root);
        return res;
    }

private:
    map<int,int> mp;
    vector<int> res;
    int count = 0;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        mp[root->val]++;
        if (mp[root->val] > count) {
            res.clear();
            res.push_back(root->val);
            count = mp[root->val];
        } else if (mp[root->val] == count) {
            res.push_back(root->val);
        }
        traversal(root->right);
    }    
};