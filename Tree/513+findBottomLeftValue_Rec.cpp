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
    void traversal (TreeNode* root, int depth) {
        if (root == NULL) return;

        if (!root->left && !root->right) {
            MAX_RES = depth > MAX_DEPTH ? root->val : MAX_RES;
            MAX_DEPTH = depth > MAX_DEPTH ? depth : MAX_DEPTH;
        }

        if (root->left) {
            ++depth;
            traversal(root->left, depth);
            --depth;
        }

        if (root->right) {
            ++depth;
            traversal(root->right, depth);
            --depth;
        }

        return;
    }

    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return MAX_RES;
    }

private:
    int MAX_DEPTH = INT_MIN;
    int MAX_RES;    
};