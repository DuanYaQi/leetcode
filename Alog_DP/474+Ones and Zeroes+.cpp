class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        /*预处理01个数*/
        for (int i = 0; i < strs.size(); ++i) {
            int zeroN = 0, oneN = 0;
            for (auto &c : strs[i]) {
                if (c == '0') zeroN++;
                else oneN++;
            }
            nums[i][0] = zeroN;
            nums[i][1] = oneN;
        } 


        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

        for (int i = 1; i <= strs.size(); ++i) {
            int zeroN = nums[i-1][0], oneN = nums[i-1][1];

            for (int j = m; j >= 0; --j) {      // m 要求 0
                for (int k = n; k >= 0; --k) {  // n 要求 1
                    if (j - zeroN < 0 || k - oneN < 0) {
                        dp[i][j][k] = dp[i-1][j][k];
                    } else {
                        dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-zeroN][k-oneN]+1);   // 这里要加value +1了
                    }
                }
            }
        }

        return dp[len][m][n];
    }
};


// 滚动数组优化至2维
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        /*预处理01个数*/
        for (int i = 0; i < strs.size(); ++i) {
            int zeroN = 0, oneN = 0;
            for (auto &c : strs[i]) {
                if (c == '0') zeroN++;
                else oneN++;
            }
            nums[i][0] = zeroN;
            nums[i][1] = oneN;
        } 


        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < strs.size(); ++i) {
            int zeroN = nums[i][0], oneN = nums[i][1];

            for (int j = m; j >= 0; --j) {      // m 要求 0     一定要逆着遍历,这样dp保存的还是上一时刻的状态
                for (int k = n; k >= 0; --k) {  // n 要求 1     一定要逆着遍历,这样dp保存的还是上一时刻的状态
                    if (j - zeroN < 0 || k - oneN < 0) {
                        dp[j][k] = dp[j][k];
                    } else {
                        dp[j][k] = max(dp[j][k], dp[j-zeroN][k-oneN]+1);
                    }
                }
            }
        }

        return dp[m][n];
    }
};