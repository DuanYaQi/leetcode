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


        for (int i = 0; i < nums.size(); ++i) {
            if (uset.find(nums[i]) == uset.end()) {
                uset.insert(nums[i]);
                resT.push_back(nums[i]);
                dfs(nums);
                resT.pop_back();
                uset.erase(nums[i]);
            }
        }


        return;
    }

    vector<vector<int>> permute(vector<int>& nums) {
        //sort(nums.begin(), nums.end());
        dfs(nums);

        return res;
    }   
};