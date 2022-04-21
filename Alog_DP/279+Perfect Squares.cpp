// 优化状态转移方程
class Solution {
public:
    
    int numSquares(int n) {
        int maxn = sqrt(n); //找到搜索上界 3

        const int inf = 0x3f3f3f3f;
        int dp[maxn + 1][n + 1]; memset(dp, inf, sizeof(dp)); //前i个数，其平方数的和构成i的最少数量
        
        for (int i = 0; i <= maxn; ++i) 
            dp[i][0] = 0;
        
        for (int i = 1; i <= maxn; ++i) {
            int w = i * i;
            for (int j = 0; j <= n; ++j) {
                if (j - w < 0) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-w] + 1);
                }
            }
        }

        return dp[maxn][n];
    }
};