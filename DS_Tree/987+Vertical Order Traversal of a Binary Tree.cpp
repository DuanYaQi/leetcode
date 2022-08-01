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
    void dfs(TreeNode* root, int x, int y) {
        if (root == nullptr) return;
        dfs(root->left, x - 1, y + 1);
        vecs.emplace_back(x, y, root->val);
        dfs(root->right, x + 1, y + 1);
        return;
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        sort(vecs.begin(), vecs.end());

        vector<vector<int>> res;

        int lastX = INT_MIN;
        for (auto const &[x, y, val] : vecs ) {
            if (x != lastX) {
                lastX = x;
                res.emplace_back();
            }

            res.back().push_back(val);
        }

        return res;
    }
private:
    vector<tuple<int, int, int>> vecs;    
};


const int maxn = 1e3 + 5;
class Solution {
public:
    struct Node {
        int val;
        int x;
        int y;
    } matN[maxn];

    void dfs(TreeNode* root, int x, int y) {
        if (root == nullptr) return;
        dfs(root->left, x - 1, y + 1);
        matN[idx++] = {root->val, x, y};
        dfs(root->right, x + 1, y + 1);
        return;
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        idx = 0;
        dfs(root, 0, 0);

        vector<vector<int>> res;

        int lastX = INT_MIN;
        for (int i = 0; i < idx; i++) {
            cout << matN[idx].val << " " << matN[idx].x << " " << matN[idx].y << endl;
            if (matN[i].x != lastX) {
                lastX = matN[i].x;
                res.emplace_back();
            }
            
            res.back().push_back(matN[i].val);
        }

        return res;
    }

private:

    int idx;
};