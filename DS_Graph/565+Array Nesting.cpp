class Solution {
public:

    int dfs(vector<int> &nums, int n, vector<bool> &isVis) {
        if (isVis[n]) {
            return 0;
        }

        isVis[n] = true;        

        return 1 + dfs(nums, nums[n], isVis);
    }

    int arrayNesting(vector<int>& nums) {
        vector<bool> isVis(nums.size(), 0);
        for (int i = 0; i < nums.size(); ++i) {
            int cnt = dfs(nums, nums[i], isVis);
            mLongest = max(mLongest, cnt);
        }
        
        return mLongest;
    }

private:
    int mLongest = -1;    
};