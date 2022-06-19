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
    typedef pair<long, int> pli; 
public:
    void getSum(TreeNode* root, int &val) {
        if (root == nullptr) return;

        val += root->val;
        getSum(root->left, val);
        getSum(root->right, val);

        return;
    }

    static bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second ? true : false;
    }

    vector<int> findFrequentTreeSum(TreeNode* root) {
        map<int, int> mp;

        queue<TreeNode*> q;
        q.push(root);

        while (q.size()) {
            int size = q.size();

            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front(); q.pop();
                int val = 0;
                getSum(node, val);
                mp[val]++;
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }

        vector<int> res;
        vector<pair<int, int>> tmpv(mp.begin(), mp.end());
        sort(tmpv.begin(), tmpv.end(), cmp);

        int maxn = -1;
        for (auto iter = tmpv.begin(); iter != tmpv.end(); iter++) {
            if (maxn == -1) {
                res.push_back(iter->first);
                maxn = iter->second;
            } else if (iter->second == maxn) {
                res.push_back(iter->first);
            } else {
                break;
            }
            // cout << iter->first << " " << iter->second << endl;
        }


        return res;
    }
};