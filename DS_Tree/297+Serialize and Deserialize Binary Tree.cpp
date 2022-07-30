/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    void dfs(TreeNode* root, string &s) { // 中序
        if (root == nullptr) {
            s += "-1111,";
            return;
        }
        
        s += to_string(root->val) + ",";
        dfs(root->left, s);        
        dfs(root->right, s);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        dfs(root, res);
        //cout << res;
        return res;
    }

    void stringsplit(string &s, char split, vector<int> &nums) {
        istringstream iss(s); 
        string token;
        while (getline(iss, token, split)) {
            nums.push_back(stoi(token));
        }
        return;
    }

    TreeNode* dfsBuild(vector<int> &nums, int &idx) {
        if (nums[idx] == -1111) return nullptr;
        TreeNode* root = new TreeNode(nums[idx]);
        root->left = dfsBuild(nums, ++idx);
        root->right = dfsBuild(nums, ++idx);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> nums;
        stringsplit(data, ',', nums);
        int idx = 0;
        TreeNode* res = dfsBuild(nums, idx);        
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));