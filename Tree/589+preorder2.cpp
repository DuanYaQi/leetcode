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
    vector<int> preorder(Node* root) {
        vector<int> res;
        stack<Node*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            Node* node = st.top();
            if ( node != NULL) {
                st.pop();
                int size = node->children.size();
                for (int i = size - 1; i >= 0 ; --i) {
                    st.push(node->children[i]);
                }
                st.push(node);
                st.push(NULL);
            } else {
                st.pop();
                node = st.top();
                st.pop();
                res.push_back(node->val);
            }
        }
        return res;
    }
};