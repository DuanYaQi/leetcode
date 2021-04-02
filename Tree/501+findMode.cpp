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
    vector<int> findMode(TreeNode* root) {
        traversal(root);
        return res;
    }

private:
    map<int,int> mp;
    vector<int> res;
    int count = 0;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        mp[root->val]++;
        if (mp[root->val] > count) {
            res.clear();
            res.push_back(root->val);
            count = mp[root->val];
        } else if (mp[root->val] == count) {
            res.push_back(root->val);
        }
        traversal(root->right);
    }    
};



class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        if (root == NULL) return res;
        traversal(root);
        vector<pair<int, int>> vec(mp.begin(), mp.end());
        sort(vec.begin(), vec.end(), cmp);

        res.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i].second == vec[0].second) res.push_back(vec[i].first);
            else break;
        }
        return res;
    }

    bool static cmp (const pair<int, int> a, const pair<int, int> b) {
        return a.second > b.second ? true : false;
    }

private:
    map<int,int> mp;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        mp[root->val]++;
        traversal(root->right);
    }   
};