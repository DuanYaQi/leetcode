class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));

        dp[0][0] = 0;
        dp[0][1] = -prices[0];  // 第i天 第一次买入
        dp[0][2] = 0;           // 第i天 第一次卖出
        dp[0][3] = -prices[0];  // 第i天 第二次买入
        dp[0][4] = 0;           // 第i天 第二次卖出

        for (int i = 1; i < prices.size(); ++i) {
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            dp[i][2] = max(dp[i-1][2], dp[i-1][1] + prices[i]);
            dp[i][3] = max(dp[i-1][3], dp[i-1][2] - prices[i]);
            dp[i][4] = max(dp[i-1][4], dp[i-1][3] + prices[i]);
        }

        return dp[prices.size() - 1][4];
    }
};