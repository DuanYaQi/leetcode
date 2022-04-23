class Solution {
public:
    // 把每个格子看成一个节点，相邻格子之间连边
    // 若出发格的箭头恰好指着这个方向，边的长度就是 0，否则是 1
    // 在这张图上跑一边最短路即可

    int conveyorBelt(vector<string>& matrix, vector<int>& start, vector<int>& end) {
        this->matrix = matrix;

        int m = matrix.size(), n = matrix[0].size();

        // 邻接矩阵
        const int inf = 0x3f3f3f3f;
        vector<vector<int>> g(m * n, vector<int>(m * n, inf));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int idx = i * n + j;

                for (int k = 0; k <4; ++k) {
                    int x = i + dirs[k][0];
                    int y = j + dirs[k][1];

                    if (x >= 0 && x < m && y >=0 && y < n) {
                        int iidx = x * n + y;
                        if (matrix[i][j] == s[k]) g[idx][iidx] = 0;
                        else g[idx][iidx] = 1;
                    }
                }
            }   
        }

        vector<int> dist(m*n, inf);
        int startIdx = start[0] * n + start[1];
        dist[startIdx] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, startIdx);

        while (pq.size()) {
            auto [weight, idx] = pq.top(); pq.pop();

            for (int to = 0; to < m * n; ++to) {
                if (g[idx][to] != inf) {
                    int d = weight + g[idx][to];
                    if (dist[to] > d) {
                        dist[to] = d;
                        pq.emplace(d, to);
                    }
                }
            }
        }

        int endIdx = end[0] * n + end[1];
        return dist[endIdx] == inf ? 0 : dist[endIdx];
    }

private:
    vector<string> matrix;
    short dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    char s[5] = "<>^v";
};