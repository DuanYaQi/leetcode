class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();

        vector<vector<int>> nums(len, vector<int>(2, 0));
        for (int i = 0; i < len; ++i) {
            nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
            nums[i][1] = strs[i].size() - nums[i][0];
        }

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        vector<vector<vector<int>>> path(len, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

        for (int i = 0; i < len; ++i) {
            int zeroN = nums[i][0], oneN = nums[i][1];

            for (int j = m; j >= 0; --j) {
                for (int k = n; k >= 0; --k) {
                    if (j - zeroN < 0 || k - oneN < 0) {
                        dp[j][k] = dp[j][k];
                    } else {
                        dp[j][k] = max(dp[j][k], dp[j - zeroN][k - oneN] + 1);
                        path[i][j][k] = dp[j][k];
                    }
                }
            }
        }

        int ans[len+1];
        int idx = 0, mm = m, nn = n;
        for (int i = len - 1; i >= 0; --i) {
            if (path[i][mm][nn]) {
                ans[++idx] = i;
                mm -= nums[i][0];
                nn -= nums[i][1];
            }
        }

        for (int i = idx; i > 0; --i) 
            cout << ans[i] << " ";

        return dp[m][n];
    }
};