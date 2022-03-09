class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());
        dp[0] = nums[0];

        for (int i = 1; i < nums.size(); ++i) {

            dp[i] = max(dp[i-1] + nums[i], nums[i]);
        }

        sort(dp.begin(), dp.end());
        
        return dp[nums.size()-1];
    }
};
