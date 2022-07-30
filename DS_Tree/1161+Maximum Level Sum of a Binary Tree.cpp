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
const int inf = 0x3f3f3f3f;
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        vector<pair<int, int>> vecs;
        int res = inf;

        queue<TreeNode*> q;
        q.push(root);

        int reslevel = 1, level = 1;
        while (q.size()) {          
            int size = q.size();
            int resT = 0;
            for (int i = 0; i < size; ++i) {
                auto cur = q.front(); q.pop();  
                resT += cur->val;
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            if (res < resT) {
                res = resT;
                reslevel = level;
            }
              
            level++;
        }

        return reslevel;
    }
};