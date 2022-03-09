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
//Stack实现
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        stack<TreeNode*> st;
        if (root != NULL) {
            st.push(root->left);
            st.push(root->right);
        }

        while (!st.empty()) {
            TreeNode* rightn = st.top();    st.pop();
            TreeNode* leftn  = st.top();    st.pop();

            if (!rightn && !leftn) {
                continue;
            }

            if (!rightn || !leftn || (rightn->val != leftn->val)) {
                return false;
            }
            st.push(rightn->right); st.push(leftn->left);
            st.push(leftn->right); st.push(rightn->left);
        }
        return true;
    }
};