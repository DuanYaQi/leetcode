class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int m = s.size(); 
    
        bool dp[m + 1]; memset(dp, false, sizeof(dp));   //表示前 i 个单词，是否可以组成长度为 j 的字符串 

        dp[0] = true;

        for (int i = 1; i <= m; ++i) {
            
            for (int j = 0; j < wordDict.size(); ++j) {
                string str = wordDict[j];
                int sSize = str.size();
                if (i - sSize >= 0 && str == s.substr(i - sSize, sSize))
                    dp[i] = dp[i] || dp[i - sSize];
            }
        }

        return dp[m];
    }
};