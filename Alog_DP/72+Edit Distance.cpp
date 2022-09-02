class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; ++i)
            dp[i][0] = i;

        for (int i = 1; i <= n2; ++i)
            dp[0][i] = i;

        int add, del, change;
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                add = dp[i-1][j] + 1;
                del = dp[i][j-1] + 1;

                if (word1[i - 1] == word2[j - 1]) {
                    change = dp[i-1][j-1];
                } else {
                    change = dp[i-1][j-1] + 1;
                }

                dp[i][j] = min(add, min(del, change));
            }
        }


        return dp.back().back();
    }   
};