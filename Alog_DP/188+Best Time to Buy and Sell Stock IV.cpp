class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0) return 0;

        vector<vector<int>> dp(prices.size(), vector<int>(2*k + 1, 0));

        dp[0][0] = 0;
        for (int i = 1; i < 2 * k; i+=2) {
            dp[0][i] = -prices[0];   // 奇数
        }

        for (int i = 1; i < prices.size(); ++i) {
            for (int j = 0; j < 2*k - 1; j+=2) {
                dp[i][j+1] = max(dp[i-1][j+1], dp[i-1][j] - prices[i]);   //奇数
                dp[i][j+2] = max(dp[i-1][j+2], dp[i-1][j+1] + prices[i]); //偶数
            }
        }

        return dp[prices.size()-1][2*k];
    }
};


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0) return 0;
        
        vector<vector<int>> dp(prices.size(), vector<int>(2*k + 1, 0));

        dp[0][0] = 0;
        for (int i = 1; i < 2 * k + 1; i++) {
            if (i & 1) dp[0][i] = -prices[0];   // 奇数
            else dp[0][i] = 0; 
            // cout << dp[0][i] << " ";
        }

        for (int i = 1; i < prices.size(); ++i) {
            for (int j = 1; j < 2*k + 1; ++j) {
                if (j & 1) dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] - prices[i]); //奇数
                else dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + prices[i]);
            }
        }


        return dp[prices.size()-1][2*k];
    }
};



