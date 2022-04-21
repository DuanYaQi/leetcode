class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        int dp[n+1][amount+1]; memset(dp, 0, sizeof(dp));   // 前i个数中选元素，元素和为j的组合数
        
        
        for (int i = 0; i <= n; ++i)    // 和0的组合数均为1，都不选
            dp[i][0] = 1;

        for (int i = 1; i <= n; ++i) {
            int w = coins[i-1];

            for (int j = 0; j <= amount; ++j) {
                if (j - w < 0) {    // 不能选
                    dp[i][j] = dp[i-1][j];
                } else {            // 能选
                    for (int k = 0; k <= (int)j / w; ++k) { // 注意这里k=0的时候就包括了 dp[i-1][j]！！！！！！！！！！！！
                        dp[i][j] += dp[i-1][j-w*k]; 
                    }
                }
            }
        }

        return dp[n][amount];
    }
};


// 优化状态转移方程
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        int dp[n+1][amount+1]; memset(dp, 0, sizeof(dp));   // 前i个数中选元素，元素和为j的组合数
        
        
        for (int i = 0; i <= n; ++i)    // 和0的组合数均为1，都不选
            dp[i][0] = 1;

        for (int i = 1; i <= n; ++i) {
            int w = coins[i-1];

            for (int j = 0; j <= amount; ++j) {
                if (j - w < 0) {    // 不能选
                    dp[i][j] = dp[i-1][j];
                } else {            // 能选
                    dp[i][j] = dp[i-1][j] + dp[i][j-w];     // 注意这里是 = 号 不是+=号
                }
            }
        }
        
        return dp[n][amount];
    }
};


// 滚动数组优化
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        int dp[amount+1]; memset(dp, 0, sizeof(dp));   // 前i个数中选元素，元素和为j的组合数
        
        
        dp[0] = 1;    // 和0的组合数均为1，都不选
            

        for (int i = 1; i <= n; ++i) {
            int w = coins[i-1];

            for (int j = 0; j <= amount; ++j) {
                if (j - w < 0) {    // 不能选
                    dp[j] = dp[j];
                } else {            // 能选
                    dp[j] = dp[j] + dp[j-w]; 
                }
            }
        }
        
        return dp[amount];
    }
};
