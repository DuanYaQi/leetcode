class Solution {
public:
    //times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));

        for (auto &t : times) {
            int x = t[0], y = t[1];
            g[x][y] = t[2];
        }

        vector<int> dist(n + 1, inf);   // 从起点到 i 的最短距离
        dist[k] = 0;    // 自身到自身为0
        vector<int> used(n + 1);

        for (int i = 1; i <= n; ++i) {
            int x = -1;
            for (int y = 1; y <= n; ++y) {  // 循环找出离当前flag节点最近的点x.   i=1 时找出来的是 k 即起点
                if (!used[y] && (x == -1 || dist[y] < dist[x])) {
                    x = y;
                }
            }

            used[x] = true;
            for (int y = 1; y <= n; ++y) {  // 更新所有最短距离
                dist[y] = min(dist[y], dist[x] + g[x][y]);  // 从起点到节点flag节点x的最短距离 dist[x]
            }
        }

        int ans = *max_element(++dist.begin(), dist.end());
        return ans == inf ? -1 : ans;
    }
};