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
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        string res;
        while(!q.empty()){
            auto p=q.front();
            q.pop();
            if(p!=NULL){
                res+=to_string(p->val);
                res+=',';
                q.push(p->left);
                q.push(p->right);
            }else res+="null,";
        }
        return res;
    }

    vector<string> split(string &data){
        int start=0;
        vector<string> res;
        while(1){
            auto end = data.find(',',start);
            if(end==string::npos)break;
            res.push_back(data.substr(start,end-start));
            start=end+1;
        }
        return move(res);
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        auto vals = split(data);
        queue<TreeNode*> q;
        if(vals[0]=="null")return NULL;
        q.push(new TreeNode(stoi(vals[0])));
        TreeNode *res=q.front();
        for(int i=1;i<vals.size();){
            if(vals[i]!="null"){
                auto p=new TreeNode(stoi(vals[i]));
                q.push(p);
                q.front()->left=p;
            }
            ++i;
            if(vals[i]!="null"){
                auto p=new TreeNode(stoi(vals[i]));
                q.push(p);
                q.front()->right=p;
            }
            ++i;
            q.pop();
        }
        return res;
    }

};
// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));