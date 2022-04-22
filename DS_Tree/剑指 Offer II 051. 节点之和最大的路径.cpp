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
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return maxSum;
    }
private:
    int maxSum = INT_MIN;

    int dfs(TreeNode* root) {
        if (root == nullptr) return 0;

        // 左右子树的最大路径和
        int leftV = max(dfs(root->left), 0);
        int rightV = max(dfs(root->right), 0);

        // 该节点的最大路径和
        int res = root->val + leftV + rightV;

        // 更新最大路径和
        maxSum = max(res, maxSum);

        // 该节点的最大贡献值，注意是贡献值不是路径和 
        return root->val + max(leftV, rightV);  //因为只能走一条路，所以要么选左，要么选右
    }    
};