class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;
    unordered_set<int> uset;

    void dfs(vector<int>& nums) {
        if (resT.size() == nums.size()) {
            res.push_back(resT);
            return;
        }

        unordered_set<int> uuset;

        for (int i = 0; i < nums.size(); ++i) {
            if (uuset.find(nums[i]) != uuset.end())
                continue;

            if (uset.find(nums[i]) == uset.end()) {
                uuset.insert(nums[i]);
                uset.insert(nums[i]);
                resT.push_back(nums[i]);
                dfs(nums);
                resT.pop_back();
                uset.erase(nums[i]);
            }
            
        }

        return;
    }


    vector<vector<int>> permuteUnique(vector<int>& nums) {
        dfs(nums);
        return res;
    }
};