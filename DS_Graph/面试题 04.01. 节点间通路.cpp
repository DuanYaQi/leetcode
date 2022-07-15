class Solution {
public:
    void dfs(vector<vector<int>> &g, vector<bool> &isArrived, int start, int target, bool &flag) {
        if (isArrived[start]) {
            return;
        }
        
        isArrived[start] = true;

        if (start == target) {
            flag = true;
            return;
        }

        for (int i = 0; i < g[start].size(); ++i) {
            dfs(g, isArrived, g[start][i], target, flag);
        }
    } 


    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<bool> isArrived(n, false);
        vector<vector<int>> g(n);

        for (auto &edge : graph) {
            g[edge[0]].push_back(edge[1]);
        }

        bool flag = false;
        dfs(g, isArrived, start, target, flag);

        return flag;
    }
};