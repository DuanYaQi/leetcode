class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;

    void dfs(vector<int>& nums, int start) {
        res.push_back(resT);

        unordered_set<int> uset;
        for (int i = start; i < nums.size(); ++i) {
            if (uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            resT.push_back(nums[i]);
            dfs(nums, i+1);
            resT.pop_back();
        }

        return;
    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return res;
    }
};