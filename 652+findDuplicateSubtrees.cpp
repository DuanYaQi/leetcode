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
private:
    unordered_map<string, int> mp;//映射
    vector<TreeNode*> res; //result
public:
    string traverse(TreeNode* root){
        if (root == nullptr) return "#";
        string l = traverse(root->left);
        string r = traverse(root->right);

        string subTree = to_string(root->val) + ',' + l + ',' + r;
        mp[subTree] ++;
        if (mp[subTree] == 2) {
            res.push_back(root);
        }
        return subTree;
    }

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        return res;
    }
};