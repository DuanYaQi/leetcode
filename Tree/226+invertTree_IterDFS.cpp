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
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top();

            if (node != nullptr) {
                st.pop();
                if (node->right != nullptr) st.push(node->right);
                if (node->left != nullptr) st.push(node->left);
                st.push(node);
                st.push(nullptr);
            } else {
                st.pop();
                node = st.top();
                st.pop();
                swap(node->left, node->right);
            }            
        }
        return root;
    }
};


class Solution2 {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);
        TreeNode* node;

        while (!st.empty()) {
            node = st.top();
            st.pop();

            if (node != nullptr) {
                if (node->right != nullptr) st.push(node->right);
                st.push(node);
                st.push(nullptr);
                if (node->left != nullptr) st.push(node->left);
                swap(node->left, node->right);
            } else {
                st.pop();
            }
        }
        return root;
    }
};