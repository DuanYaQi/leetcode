class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(4, 0));

        dp[0][0] = -prices[0];

        for (int i = 1; i < prices.size(); ++i) {
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][3], dp[i-1][1]) - prices[i]);  //第i天持有股票所得最多现金
            dp[i][1] = max(dp[i-1][1], dp[i-1][3]);           // 两天前就卖出了股票，度过了冷冻期
            dp[i][2] = dp[i-1][0] + prices[i];                // 今天卖出股票
            dp[i][3] = dp[i-1][2];                            // 今天为冷冻期状态，冷冻期状态不可持续
        }

        return max(dp[prices.size()-1][1], max(dp[prices.size()-1][2], dp[prices.size()-1][3]));
    }
};