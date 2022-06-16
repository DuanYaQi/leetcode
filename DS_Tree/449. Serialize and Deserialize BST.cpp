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
    string s = "";

    void serDfs(TreeNode* root) {
        if (root == nullptr) return;

        s += to_string(root->val) + ",";
        if (root->left != nullptr) serDfs(root->left);
        if (root->right != nullptr) serDfs(root->right); 
        return;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        serDfs(root);
        cout << s << endl;
        return s;
    }


    void stringSplit(string str, char split, vector<int>& nums)
    {
        istringstream iss(str);	// 输入流
        string token;			// 接收缓冲区
        while (getline(iss, token, split))	// 以split为分隔符
        {
            nums.push_back(atoi(token.c_str()));
            cout << token << endl; // 输出
        }
    }

    TreeNode* buildTree(const vector<int> &pre, int preS, int preE, 
                        const vector<int> &in, int inS, int inE) {
        if (preS > preE || inS > inE) return nullptr;
        
        TreeNode* root = new TreeNode(pre[preS]);
        int midIdx = -1;
        for (int i = inS; i <= inE; i++) {
            if (in[i] == pre[preS]) {
                midIdx = i;
                break;
            }
        }

        root->left = buildTree(pre, preS + 1, preS + midIdx - inS,
                                in, inS, midIdx - 1);
        root->right = buildTree(pre, preS + midIdx - inS + 1, preE,
                                in, midIdx + 1, inE);

        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;
 
        vector<int> preNums;
        stringSplit(data, ',', preNums);

        vector<int> inNums = preNums;
        sort(inNums.begin(), inNums.end());
        

        return buildTree(preNums, 0, preNums.size() - 1,
                        inNums, 0, inNums.size() - 1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;








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
    void stringSplit(string str, char split, vector<int>& nums)
    {
        istringstream iss(str);	// 输入流
        string token;			// 接收缓冲区
        while (getline(iss, token, split))	// 以split为分隔符
        {
            nums.push_back(atoi(token.c_str()));
            //cout << token << endl; // 输出
        }
    }

    void dfs(TreeNode* root, string &s) {
        if (root == nullptr) return;

        s += to_string(root->val) + "+";
        dfs(root->left, s);
        dfs(root->right, s);
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        dfs(root, s); 
        //cout << s << endl;
        return s;   
    }

    TreeNode* buildTree(vector<int> &pre, int preS, int preE,
                        vector<int> &in, int inS, int inE) 
    {
        if (preS > preE || inS > inE) return nullptr;

        TreeNode* root = new TreeNode(pre[preS]);

        int midIdx = -1;
        for (int i = inS; i <= inE; i++) {
            if (in[i] == pre[preS]) {
                midIdx = i;
                //cout << midIdx << endl;
                break;
            }
        }

        //cout << preS + 1 << " " << preS + midIdx - inS << endl;
        root->left = buildTree(pre, preS + 1, preS + midIdx - inS,
                                in, inS, midIdx - 1);
        root->right = buildTree(pre, preS + midIdx - inS + 1, preE,
                                in, midIdx + 1, inE);

        return root;
    }


    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> pre;
        stringSplit(data, '+', pre);
        vector<int> in = pre;
        sort(in.begin(), in.end());
        
        TreeNode* root = buildTree(pre, 0, pre.size() - 1,
                                    in, 0, in.size() - 1);

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
