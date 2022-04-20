// 1.朴素完全背包 O(n^3)
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        const int inf = 0x3f3f3f3f;
        int dp[n + 1][amount + 1]; memset(dp, inf, sizeof(dp)); // 前i个数字组成j的最小个数

        for (int i = 0; i <= n; ++i) 
            dp[i][0] = 0;

        for (int i = 1; i <= n; ++i) {	// 遍历物品
            int num = coins[i-1];		// 能过的原因是这一步，后边两个计算用到num了！！！！！！

            for (int j = 0; j <= amount; ++j) {	// 遍历包的体积
                for (int k = 0; k <= (int)j / num; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j - k * num] + k);
                }
            }
        }

        return dp[n][amount] == inf ? -1 : dp[n][amount];
    }
};