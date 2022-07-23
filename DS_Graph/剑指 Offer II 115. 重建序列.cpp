class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        int m = nums.size();
        vector<vector<int>> graph(m+1);
        vector<int> inDegree(m+1);

        for (auto &edge : sequences) {
            for (int i = edge.size() - 1; i > 0; --i) {  //不一定只有两个元素的
                int from = edge[i-1], to = edge[i];
                graph[from].push_back(to);  // 无权图
                inDegree[to]++;
            }
        }

        
        queue<int> q;
        for (int i = 1; i <= m; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (q.size()) {
            int size = q.size();

            if (size > 1) return false;
            
            int u = q.front(); q.pop();
            for (int i = 0; i < graph[u].size(); ++i) {
                int to = graph[u][i];
                inDegree[to]--;
                if (inDegree[to] == 0) {
                    q.push(i);
                }
            }
        }

        return true;
    }   
};