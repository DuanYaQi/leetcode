class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        queue<int> q;
        q.push(start);
        
        bool vis[n+1]; memset(vis, false, sizeof vis);

        while (!q.empty()) {
            int idx = q.front(); q.pop();

            if (arr[idx] == 0) 
                return true;
                
            if (vis[idx]) continue;
            vis[idx] = true;

            if (idx + arr[idx] < n) q.push(idx + arr[idx]);
            if (idx - arr[idx] >= 0) q.push(idx - arr[idx]);           
        }

        return false;
    }
};