class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            TreeNode* newN = new TreeNode(val);
            newN->left = root;
            return newN;
        }
        int nowd = 1;

        queue<TreeNode*> q;
        q.push(root);

        vector<TreeNode*> wait;
        while (q.size()) {
            int size = q.size(); 

            
            for (int i = 0; i < size; ++i) {
                auto cur = q.front(); q.pop();

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);

                if (nowd == depth - 1) {
                    wait.emplace_back(cur);
                }
            }

            nowd++;
        }

        for (auto &pa : wait) {
            TreeNode* leftN = pa->left;
            TreeNode* rightN = pa->right;
            TreeNode* newN = new TreeNode(val);
            if (leftN != nullptr) {
                pa->left = newN;
                newN->left = leftN;
            } else {
                pa->left = newN;
            }

            newN = new TreeNode(val);
            if (rightN) {
                pa->right = newN;
                newN->right = rightN;
            } else {
                pa->right = newN;
            }
        }

        return root;
    }
};