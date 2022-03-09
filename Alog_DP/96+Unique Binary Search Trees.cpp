class Solution {
public:
    int numTrees(int n) {
        int dp[n+1]={};
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; ++i) {

            for (int mid = 1; mid <= i; ++mid) {
                dp[i] += dp[mid-1]*dp[i-mid];
            }
        }

        return dp[n];
    }
};