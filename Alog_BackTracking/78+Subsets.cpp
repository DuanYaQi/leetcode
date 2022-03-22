class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;
    void dfs(vector<int>& nums, int start){
        if (start >= nums.size()) {
            return;
        }
        res.push_back(resT);
        

        for (int i = start; i < nums.size(); ++i) {
            resT.push_back(nums[i]);
            dfs(nums, i + 1);
            resT.pop_back();
        }

        return;
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return res;
    }
};