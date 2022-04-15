class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;

        // 记录最短路径
        vector<int> dist(n + 1, inf);
        dist[k] = 0;

        // n-1次松弛操作 不断更新最短路径
        for (int i = 1; i < n; ++i) {
            bool flag = false;
            for (auto &t : times) {
                if (dist[t[1]] > dist[t[0]] + t[2]) {
                    dist[t[1]] = dist[t[0]] + t[2];
                    flag = true;
                }
            }
            if (!flag) break;   // 当这次不更新了 之后一定不会更新了 直接退出
        }

        int res = *max_element(++dist.begin(), dist.end());
        return res == inf ? -1 : res;
    }
};