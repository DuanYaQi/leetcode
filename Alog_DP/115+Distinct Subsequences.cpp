int numDistinct(string s, string t) {
    int n1 = s.size(), n2 = t.size();
    // dp[i][j] 表示 s 前 i 个字符串包含 t 的前 j 个字符串的个数
    vector<vector<unsigned long long>> dp(n1 + 1, vector<unsigned long long>(n2 + 1, 0));

    for (int i = 0; i <= n1; ++i) 
        dp[i][0] = 1;

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (s[i - 1] == t[j - 1]) {  //不相等
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp.back().back();
}