class Solution {
public:
    bool vis[16] = {false};
    vector<vector<int>> res;

    void dfs(int u, int end, vector<vector<int>>& graph, vector<int>& resT) {
        vis[u] = true;
        if (u == end) res.push_back(resT);
        
        for (int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i];
            if (vis[v] == false) {
                resT.push_back(v);
                dfs(v, end, graph, resT);
                vis[v] = false;
                resT.pop_back();
            }
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int end = graph.size() - 1;
        vector<int> resT;
        resT.push_back(0);
        dfs(0, end, graph, resT);

        return res;
    }
};