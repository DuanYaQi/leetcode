class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<pair<int, int>>> g(n + 1);

        for (auto &t : times) {
            g[t[0]].emplace_back(t[1], t[2]);
        }

        // 记录最短路径
        vector<int> dist(n + 1, inf);
        dist[k] = 0;

        queue<int> q;
        q.emplace(k);
        unordered_set<int> s;
        s.emplace(k);

        
        while (q.size()) {
            int cur = q.front(); q.pop();
            s.erase(cur);

            for (auto &e : g[cur]) {
                int x = e.first, d = dist[cur] + e.second;
                if (dist[x] > d) {
                    dist[x] = d;
                    
                    if (s.count(x) == 0) {  // x不在集合中
                        q.emplace(x);
                        s.emplace(x);
                    }
                }
            }
        }
         

        int res = *max_element(++dist.begin(), dist.end());
        return res == inf ? -1 : res;
    }
    
};