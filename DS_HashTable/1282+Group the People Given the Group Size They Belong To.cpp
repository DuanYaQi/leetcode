const int maxn = 5e2 + 5;
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        int maxn = *max_element(groupSizes.begin(), groupSizes.end());

        vector<stack<vector<int>>> res(maxn + 1);
        for (int i = 0; i < groupSizes.size(); ++i) {
            int idx = groupSizes[i];
            if (res[idx].empty()) {
                res[idx].push(vector<int>{i});
            } else {
                if (res[idx].top().size() == i) {
                    res[idx].push(vector<int>{i});
                } else {
                    res[idx].top().push_back(i);
                }
            }
        }
        
        vector<vector<int>> ans;
        for (int i = 0; i <= maxn; ++i) {
            if (res[i].empty()) continue;
            while (!res[i].empty()) {
                ans.push_back(res[i].top()); res[i].pop();
            }            
        }
        return ans;      
    }
};