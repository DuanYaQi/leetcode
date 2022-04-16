/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    set<int> st;

    /*把所有节点放入set中，BST中序得到有序数组，不过无所谓，set就是有序的*/
    void dfs(TreeNode* node) {  
        if (node == nullptr) return;
        dfs(node->left);
        st.insert(node->val);
        dfs(node->right);
    }

public:

    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        dfs(root);

        int cnt = 0;

        for (int i = ops.size() - 1; i >= 0; --i)  {   //1e5 倒着来
            if (!st.size()) break;	// 剪枝:set为空说明全染好了，直接break即可
            
            // lower_bound 寻找在数组或容器范围内第一个值大于等于val元素的位置
            while (true) {
                // ops[i][1] = start
                // ops[i][2] = end
                // 值必须在 ops[i][1]~ops[i][2] 左闭右闭之间才能染色并从 set 中删除
                auto it = st.lower_bound(ops[i][1]);	// 找第一个值大于等于start元素的位置
                if (it == st.end()) break;				// 剪枝：如果没有大于等于start的值,即所有值都小于start,不在染色区间, *(it++)>=(*it) 没必要在while中退出
                if (*it > ops[i][2]) break;				// 剪枝：如果该值比end还大,不在染色区间，*(it++)>=(*it) 没必要在while中退出
                st.erase(*it);	// 删除这个元素 这个元素值必在  之间 
                if (ops[i][0]) cnt++;
            }

        }

        return cnt;
    }
};