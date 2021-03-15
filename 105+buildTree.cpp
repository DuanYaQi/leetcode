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
    /* 
   若前序遍历数组为 preorder[preStart..preEnd]，
   后续遍历数组为 postorder[postStart..postEnd]，
   构造二叉树，返回该二叉树的根节点 
    */
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd, 
                vector<int>& inorder, int inStart, int inEnd) {
        if(preStart > preEnd) {
            return nullptr;
        }
        
        // rootVal 在中序遍历数组中的索引
        int index = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == preorder[preStart]) {
                index = i;
                break;
            }
        }

        TreeNode* root = new TreeNode(preorder[preStart]);
        // 递归构造左右子树
        root->left = build(preorder, preStart + 1, preStart + index - inStart,
                        inorder, inStart, index - 1);

        root->right = build(preorder, preStart + index - inStart + 1, preEnd,
                        inorder, index + 1, inEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
};