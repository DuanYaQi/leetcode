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
    void traversal (Node* root) {
        if (root == NULL) return;
        int size = root->children.size();

        res.push_back(root->val);
        for (int i = 0; i < size; ++i) {
            traversal(root->children[i]);
        }
    }
    vector<int> preorder(Node* root) {
        traversal(root);
        return res;
    }
private:
    vector<int> res;    
};