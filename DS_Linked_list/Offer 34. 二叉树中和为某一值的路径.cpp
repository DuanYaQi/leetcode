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
    void dfs(TreeNode* root, int sumn) {
        if (root->left == nullptr && root->right == nullptr && sumn == mtarget) {
            res.push_back(resT);
        }

        if (root->left) {
            resT.push_back(root->left->val);
            dfs(root->left, sumn + root->left->val);
            resT.pop_back();
        }

        if (root->right) {
            resT.push_back(root->right->val);
            dfs(root->right, sumn + root->right->val);
            resT.pop_back();
        }
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if (root == nullptr) return {};
        mtarget = target;
        resT.push_back(root->val);
        dfs(root, root->val);
        return res;
    }

private:
    vector<vector<int>> res;
    vector<int> resT;    
    int mtarget;
};