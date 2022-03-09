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
    int maxDepth(Node* root) {
        queue<Node*> que;
        if (root == NULL) return 0;
        int depth = 0;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();

            for ( int i = 0; i < size; ++i) {
                Node* node = que.front(); que.pop();
                for (int j = 0; j < node->children.size(); ++j) {
                    que.push(node->children[j]);
                }
            }
            ++depth;
        }
        return depth;
    }
};