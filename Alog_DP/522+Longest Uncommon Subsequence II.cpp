class Solution {
public:
    bool isSubsequence(string &s1, string &s2) {
        int m = s1.size(), n = s2.size();

        if (m > n) {
            return false;
        }

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i < m + 1; ++i) {
            for (int j = 1; j < n + 1; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[m][n] == m;   // m一定是最小的
    }

    int findLUSlength(vector<string>& strs) {
        int res = -1;
        for (int i = 0; i < strs.size(); ++i) {
            bool flag = true;
            for (int j = 0; j < strs.size(); ++j) {
                if (i == j) continue;
                
                if (isSubsequence(strs[i], strs[j])) {  //如果它是其它字符串的子串
                    flag = false;
                    break;
                } 
            }
            
            if (flag) res = max(res, (int)strs[i].size());
        }    

        return res;
    }
};