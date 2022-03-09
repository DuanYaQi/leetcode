class Solution {
public:
    int robRange(vector<int>& nums, int start, int end) {
        if (end - start == 0) return nums[start];
        if (end - start == 1) return max(nums[start], nums[start + 1]);

        int dp[nums.size()+1];
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; ++i) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        return dp[end];
    }

    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int noStart = robRange(nums, 1, n-1);
        int noEnd = robRange(nums, 0, n-2);
        return max(noStart, noEnd);
    }
};