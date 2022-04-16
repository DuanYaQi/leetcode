int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int inf = INT_MAX / 2;

    vector<vector<pair<int, int>>> g(n + 1);
    for (auto &t : times) {
        g[t[0]].emplace_back(t[1], t[2]);
    }

    vector<int> dist(n + 1, inf);
    dist[k] = 0;

    vector<bool> visited(n + 1, false);

    /*queue*/
    auto myCmp = [](const auto& e1, const auto& e2) {
        auto&& [to1, w1] = e1;
        auto&& [to2, w2] = e2;
        return w1 > w2; // 小顶堆 返回的是下沉规则，true则下沉 即值大的下沉
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(myCmp)> pq(myCmp);
    pq.emplace(k, 0);

    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        int x = p.first;

        if (visited[x]) continue;
        visited[x] = true;

        for (auto &e : g[x]) {
            int y = e.first, d = dist[x] + e.second;
            if (dist[y] > d) {
                dist[y] = d;
                pq.emplace(y, d);
            }
        }
    }

    int res = *max_element(++dist.begin(), dist.end());    
    return res == inf ? -1 : res;    
}






struct HeapNode {
    int u;
    int d;

    HeapNode(int uu, int dd) : u(uu), d(dd) { }

    bool operator<(const HeapNode &node) const {
        return d > node.d;  // 小顶堆
    }
};


int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int inf = INT_MAX / 2;

    vector<vector<pair<int, int>>> g(n + 1);
    for (auto &t : times) {
        g[t[0]].emplace_back(t[1], t[2]);
    }

    vector<int> dist(n + 1, inf);
    dist[k] = 0;

    vector<bool> visited(n + 1, false);

    /*queue*/
    priority_queue<HeapNode> pq;
    pq.emplace(k, 0);

    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        int x = p.u;

        if (visited[x]) continue;
        visited[x] = true;

        for (auto &e : g[x]) {
            int y = e.first, d = dist[x] + e.second;
            if (dist[y] > d) {
                dist[y] = d;
                pq.emplace(y, d);
            }
        }
    }

    int res = *max_element(++dist.begin(), dist.end());    
    return res == inf ? -1 : res;    
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int inf = INT_MAX / 2;

    vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));
    for (auto &t : times) {
        g[t[0]][t[1]] = t[2];
    }

    vector<int> dist(n + 1, inf);
    dist[k] = 0;

    vector<bool> visited(n + 1, false);

    /*queue*/
    auto myCmp = [](const auto& e1, const auto& e2) {
        auto&& [to1, w1] = e1;
        auto&& [to2, w2] = e2;
        return w1 > w2; // 小顶堆
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(myCmp)> pq(myCmp);
    pq.emplace(k, 0);

    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        int x = p.first;

        if (visited[x]) continue;
        visited[x] = true;

        for (int y = 1; y <= n; ++y) {
            int d = dist[x] + g[x][y];
            if (dist[y] > d) {
                dist[y] = d;
                pq.emplace(y, d);
            }
        }
    }

    int res = *max_element(++dist.begin(), dist.end());    
    return res == inf ? -1 : res;    
}



struct HeapNode {
    int u;
    int d;

    HeapNode(int uu, int dd) : u(uu), d(dd) { }

    bool operator<(const HeapNode &node) const {
        return d > node.d;  // 小顶堆
    }
};


int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int inf = INT_MAX / 2;

    vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));
    for (auto &t : times) {
        g[t[0]][t[1]] = t[2];
    }

    vector<int> dist(n + 1, inf);
    dist[k] = 0;

    vector<bool> visited(n + 1, false);

    /*queue*/
    priority_queue<HeapNode> pq;
    pq.push(HeapNode(k, 0));

    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        int x = p.u;

        if (visited[x]) continue;
        visited[x] = true;

        for (int y = 1; y <= n; ++y) {
            int d = dist[x] + g[x][y];
            if (dist[y] > d) {
                dist[y] = d;
                pq.push(HeapNode(y, d));
            }
        }
    }

    int res = *max_element(++dist.begin(), dist.end());    
    return res == inf ? -1 : res;    
}