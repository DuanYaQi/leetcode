class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size(); 
        vector<vector<int>> newtasks = tasks;
        for (int i = 0; i < n; ++i) {
            newtasks[i].push_back(i);
        }

        sort(newtasks.begin(), newtasks.end()); // 默认第一个元素升序排
        
        auto cmp2 = [] (const vector<int> &v1, const vector<int> &v2) {
            if (v1[1] == v2[1]) return v1[2] > v2[2];
            return v1[1] > v2[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp2)> pq(cmp2);

        int i = 0;
        long long nowTime = newtasks[i][0];
        for (; i < n && newtasks[i][0] <= nowTime; i++) {
            pq.push(newtasks[i]);
        }

        vector<int> res;
        while (pq.size()) {
            auto cur = pq.top(); pq.pop();
            res.push_back(cur[2]);

            if (pq.empty() && i < n) {
                nowTime = nowTime + cur[1] > newtasks[i][0] ? 
                            nowTime + cur[1] : newtasks[i][0]; //跳过空闲的时间
            } else {
                nowTime += cur[1];
            }
            
            while (i < n && newtasks[i][0] <= nowTime) {
                pq.push(newtasks[i++]);
            }
        }

        return res;
    }
};