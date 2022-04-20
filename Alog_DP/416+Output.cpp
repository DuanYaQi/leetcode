class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();

        int sumn = accumulate(nums.begin(), nums.end(), 0);

        if (sumn & 1) return false;

        int target = sumn / 2;

        vector<bool> dp(target + 1, false);
        vector<vector<bool>> path(n, vector<bool>(target + 1, false)); // path
        dp[0] = true;

        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            for (int j = target; j >= 0; --j) {
                if (j - num < 0) {
                    dp[j] = dp[j];
                } else {
                    dp[j] = dp[j] | dp[j-num];
                    path[i][j] = dp[j];
                }
            } 
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= target; ++j) {
                cout << path[i][j] << " ";
            } 
            cout << endl;
        }

        int ans[n];
        int k = 0;
        for (int i = n-1; i >= 0; --i) {
            if (path[i][target]) {
                ans[++k] = i;
                target -= nums[i];
            }
        }

        for (int i = k; i > 0; --i) 
            cout << ans[i] << " ";
        

        return dp[sumn / 2];
    }
};