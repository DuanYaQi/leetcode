class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));

        for (auto &t : times) {
            g[t[0]][t[1]] = t[2];
        }

        
        for (int x = 1; x <= n; x ++)
            g[x][x] = 0;
        

        for (int mid = 1; mid <= n; mid++) {
            for (int x = 1; x <= n; ++x) {
                for (int y = 1; y <= n; ++y) {
                    g[x][y] = min(g[x][y], g[x][mid] + g[mid][y]);
                }
            }
        }

        int res = *max_element(++g[k].begin(), g[k].end());
        return res == inf ? -1 : res;
    }

};