class Solution {
public: 
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();

        int dp[target+1]; memset(dp, 0, sizeof(dp));     // dp[0] 组合成 target 的方案数
        
        dp[0] = 1;

        for (int i = 1; i <= target; ++i) {             // 遍历每个值
            for (int j = 0; j < n; ++j) {              
                int num = nums[j];                      
                if (i - num >= 0 && dp[i] < INT_MAX - dp[i - num] ) { 
                    dp[i] += dp[i-num];
                }
            }
        }

        return dp[target];
    }
};