class Solution {
private:
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  

public:

    //极大值最小化
    int minimumEffortPath(vector<vector<int>>& heights) {
        const int inf = INT_MAX / 2;
        int m = heights.size();     // m 行
        int n = heights[0].size();  // n 列
        int nodeNum = m * n;
        
        vector<int> dist(nodeNum, inf);
        dist[0] = 0;

        vector<bool> visited(nodeNum, false);

    
        auto myCmp = [] (const auto &e1, const auto &e2) {
            auto&& [u1, v1, w1] = e1;
            auto&& [u2, v2, w2] = e2;
            return w1 > w2;     // 小顶堆
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(myCmp)> pq(myCmp);
        pq.emplace(0, 0, 0);    // 必须存xy而不是idx，因为后边要通过xy来计算newX和newY

        while (pq.size()) {
            auto [x, y, d] = pq.top(); pq.pop();
            int idx = x * n + y;

            if (visited[idx]) continue;
            visited[idx] = true;

            for (int i = 0; i < 4; ++i) {
                int newX = x + dirs[i][0];
                int newY = y + dirs[i][1];
                int newIdx = newX * n + newY;

                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {   // 不越界
                    int nowD = max(d, abs(heights[x][y] - heights[newX][newY]));    // 新的距离 极大值

                    if (dist[newIdx] > nowD) {  // 松弛 最小化
                        dist[newIdx] = nowD;
                        pq.emplace(newX, newY, nowD);
                    }
                }
                
            }
        }

        return dist[nodeNum - 1];
    }
};