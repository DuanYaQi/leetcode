class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();

        // dp[i][j] 表示  字符串word1前i个字符串 变成 word2 前j个字符所需要的最小步数
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 0; i <= n1; ++i)
            dp[i][0] = i;

        for (int j = 0; j <= n2; ++j)
            dp[0][j] = j;

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(dp[i-1][j-1] + 2, min(dp[i-1][j] + 1, dp[i][j-1] + 1));
                }
            }
        }

        return dp.back().back();
    }
};