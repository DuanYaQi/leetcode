class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {

        vector<vector<pair<float, int>>> g(n);      // !!!!!!!!!!!!!!注意是float

        /* !!!!!!!!!!!!!!注意是建无向图 */
        for (int i = 0; i < edges.size(); ++i) {
            g[edges[i][0]].emplace_back(succProb[i], edges[i][1] );
            g[edges[i][1]].emplace_back(succProb[i], edges[i][0]);
        }

        vector<float> dist(n, 0.0);     // 注意初始化为0.0
        dist[start] = 1.0;              // 注意起点为1.0
        vector<bool> visited(n, false);

        priority_queue<pair<float, int>, vector<pair<float, int>>, less<>> q;   // 注意less表示大顶堆，数字大的靠前
        q.emplace(1.0, start);

        while (q.size()) {
            auto p = q.top(); q.pop();
            float prob = p.first;   // 注意float
            int x = p.second;

            if (x == end) break;    // 注意搜到end可以直接退出
            if (visited[x]) continue;
            visited[x] = true;
            
            for (auto &e : g[x]) {
                float d = dist[x] * e.first; // 注意float
                int y = e.second;
                if (d > dist[y]) {  // 注意是大的时候才替换
                    dist[y] = d;
                    q.emplace(d, y);
                }
            }
        }
        /*
        for (auto & s : dist) {
            cout << s << " ";
        }
        */
        return dist[end];    // 注意直接输出指定位置答案即可   

    }
};