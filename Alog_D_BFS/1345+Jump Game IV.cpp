class Solution {
    typedef pair<int, int> pii;

public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        
        // 保存相同值
        unordered_map<int, vector<int>> ump;
        
        for (int i = 0; i < n; ++i)
            ump[arr[i]].push_back(i);
        
        bool vis[n]; memset(vis, false, sizeof vis); // 不加vis数组会超时,每个结点访问一次进行一次计算即可

        queue<pii> q;    // pari 存 idx 和 step
        q.emplace(0, 0);

        int step = 0;
        while (q.size()) {
            auto [idx, step] = q.front(); q.pop();
            
            if (idx == n-1) return step;    // 搜到末尾，输出结果

            if (vis[idx]) continue;
            vis[idx] = true;
            
            int v = arr[idx];
            step++;

            // 处理 idx-1 的情况
            if (idx + 1 < n) q.emplace(idx+1, step);
            
            // 处理 idx+1 的情况
            if (idx - 1 >= 0) q.emplace(idx-1, step);
            
            // 处理值相等的情况
            for (auto &sameValueIdx : ump[arr[idx]]) {
                q.emplace(sameValueIdx, step);
            }

            ump.erase(arr[idx]);
        }

        return -1;
    }
};