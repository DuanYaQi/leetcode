class Solution {
public:
    void dfs(int vertex, vector<vector<int>>& res, bool vis[], vector<vector<int>>& edgesNew, int start) {
        vis[vertex] = true;
        for (int i = 0; i < edgesNew[vertex].size(); ++i) {
            int vertexNext = edgesNew[vertex][i];
            if (vis[vertexNext] == false) {
                res[vertexNext].push_back(start);
                dfs(vertexNext, res, vis, edgesNew, start);
            }
        }

    }

    bool static cmp(vector<int> a, vector<int> b) {
        return a[0] < b[0];
    }

    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), cmp);
        int edgeNum = edges.size();

        vector<vector<int>> edgesNew;
        int index = 0;
        for (int i = 0; i < n; i++) {
            vector<int> edgeT;
            if (index < edgeNum) {
                while (edges[index][0] == i) {
                    edgeT.push_back(edges[index][1]);
                    index++;
                    if (index >= edgeNum) break;
                }
            }

            edgesNew.push_back(edgeT);
        }

        
        vector<vector<int>> res(n);
        for (int i = 0; i < edgesNew.size(); i++) {
            bool vis[1001] = {false};
            dfs(i, res, vis, edgesNew, i);
        }
        return res;
    }
};