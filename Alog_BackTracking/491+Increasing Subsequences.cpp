class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;
    void dfs(vector<int>& nums, int start) {
        if (resT.size() >= 2) {
            res.push_back(resT);
        }

        unordered_set<int> uset;

        for (int i = start; i < nums.size(); ++i) {
            if (uset.find(nums[i]) != uset.end()) {
                continue;
            }

            if (resT.size() == 0 || nums[i] >= resT.back()) {
                uset.insert(nums[i]);
                resT.push_back(nums[i]);
                dfs(nums, i+1);
                resT.pop_back();
            }
        }

        return;
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {

        dfs(nums, 0);
        return res;
    }
};