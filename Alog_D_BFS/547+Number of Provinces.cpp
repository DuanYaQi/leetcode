class Solution {
public:
    bool vis[205];
    

    void dfs(vector<vector<int>>& isConnected, int u) {
        vis[u] = true;
        for (int i = 0; i < isConnected.size(); ++i) {
            if (isConnected[u][i] != 0 && vis[i] == false)
                dfs(isConnected, i);
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int res = 0;

        for (int i = 0; i < isConnected.size(); ++i) {
            vis[i] = false;
        }

        for (int i = 0; i < isConnected.size(); ++i) {
            if (vis[i] == false) {
                dfs(isConnected, i);
                res++;
            }
        }
        

        return res;
    }
};