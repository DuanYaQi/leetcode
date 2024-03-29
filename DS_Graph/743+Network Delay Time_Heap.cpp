class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<pair<int, int>>> g(n + 1);    // 邻接表

        /*建图*/
        for (auto &t : times) {
            g[t[0]].emplace_back(t[1], t[2]);
        }

        vector<int> dist(n + 1, inf);
        dist[k] = 0;

    
        // 默认以 pair 的 first 元素来排序 greater<>表示数字小的优先级越大 less<>表示数字大的优先级越大
        // 等价于 priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(0, k);

        while (!q.empty()) {
            auto p = q.top(); q.pop();

            int time = p.first, x = p.second;   // 得到当前优先队列中头部元素，具有最短路径的属性

            if (dist[flag] < time) continue; // 到达flag节点有更短的路径, 不采用这一条

            for (auto &e : g[x]) {
                int y = e.first, d = dist[x] + e.second;
                if (d < dist[y]) {
                    dist[y] = d;
                    q.emplace(d, y);
                }
            }

        }

        int ans = *max_element(++dist.begin(), dist.end());
        return ans == inf ? -1 : ans;

    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<pair<int, int>>> g(n + 1);

        for (auto &t : times) {
            g[t[0]].emplace_back(t[1], t[2]);
        }

        vector<int> dist(n + 1, inf);
        dist[k] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(0, k);

        while (q.size()) {
            auto p = q.top(); q.pop();
            int time = p.first, flag = p.second;

            if (dist[flag] < time) continue; // 到达flag节点有更短的路径, 不采用这一条

            for (auto &e : g[flag]) {
                int y = e.first, d = dist[flag] + e.second;
                if ( d < dist[y]) {
                    dist[y] = d;
                    q.emplace(d, y);
                }
            }

        }

        int res = *max_element(++dist.begin(), dist.end());
        return res == inf ? -1 : res;
    }
};



class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<pair<int, int>>> g(n + 1);

        for (auto &t : times) {
            g[t[0]].emplace_back(t[1], t[2]);   //pair 只能通过 emplace_back 不能通过 push_back
        }

        vector<int> dist(n + 1, inf);
        dist[k] = 0;
        vector<bool> visit(n + 1, false);
        // visit[k] = true; //不用这一步!!!

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(0, k);

        while (q.size()) {
            auto p = q.top(); q.pop();
            int time = p.first, flag = p.second;

            if (visit[flag]) continue;
            visit[flag] = true;
            
            for (auto &e : g[flag]) {
                int y = e.first, d = dist[flag] + e.second;
                if (d < dist[y]) { // 小于!!!
                    dist[y] = d;
                    q.emplace(d, y);
                }
            }

        }

        int res = *max_element(++dist.begin(), dist.end());
        return res == inf ? -1 : res;
    }
};