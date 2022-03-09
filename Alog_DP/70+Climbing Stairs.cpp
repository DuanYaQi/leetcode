class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int dp[3];
        dp[0] = 1;
        dp[1] = 2;

        for (int i = 3; i <= n; ++i) { //直接第三层开始 i代表层数
            dp[2] = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = dp[2];
        }

        return dp[2];
    }
};