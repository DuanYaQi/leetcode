class Solution {
public: 
    int minCost(vector<vector<int>>& costs) {
        int m = costs.size();
        vector<vector<int>> dp(m, vector<int>(3, 0));
       
        for (int i = 0; i < 3; ++i)
            dp[0][i] = costs[0][i];


        for (int i = 1; i < m; ++i) {
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1];
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
        }

        

        return min(dp[m-1][0], min(dp[m-1][1], dp[m-1][2]));
    } 
};




// dp[i][j]  表示第i个房子选颜色为 j 的最小累计金额