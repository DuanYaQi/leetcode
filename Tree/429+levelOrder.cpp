/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            Node* node = que.front();
            vector<int> vec;
            int size = que.size();

            for (int i = 0; i < size; ++i) {
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (!node->children.empty()) {
                    int vsize = node->children.size();
                    for (int j = 0; j < vsize; ++j) {
                        que.push(node->children[j]);
                    }
                }    
            }
            res.push_back(vec);
        }
        return res;
    }
};