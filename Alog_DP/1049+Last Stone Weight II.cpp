//dp[i+1][j] 表示前 i 个石头能否凑出重量 j
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        
        int sumn = accumulate(stones.begin(), stones.end(), 0);
        
        int target = sumn / 2;
        
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));  //dp[i+1][j] 表示前 i 个石头能否凑出重量 j
        dp[0][0] = true;

        for (int i = 1; i <= n; ++i) {
            int num = stones[i - 1];
            
            for (int j = target; j >= 0; --j) {
                if (j - num < 0) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - num];
                }
            }
        }

        for (int j = target; j >= 0; --j) {
            if (dp[n][j]) {
                return sumn - j * 2;   
            }            
        }
        
        return 0;
    }
};


 //dp[j] 表示能否凑出重量 j
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        
        int sumn = accumulate(stones.begin(), stones.end(), 0);
        
        int target = sumn / 2;
                
        vector<int> dp(target + 1, 0);  //dp[j] 表示能否凑出重量 j
        dp[0] = true;

        for (int i = 1; i <= n; ++i) {
            int num = stones[i - 1];
            
            for (int j = target; j >= 0; --j) {
                if (j - num < 0) {
                    dp[j] = dp[j];
                } else {
                    dp[j] = dp[j] || dp[j - num];
                }
            }
        }

        for (int j = target; j >= 0; --j) {
            if (dp[j]) {
                return sumn - j * 2;   
            }            
        }
        
        return 0;
    }
};


// dp[i][j]  表示i个数字 可以组成的最大数字
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        
        int sumn = accumulate(stones.begin(), stones.end(), 0);
        
        int target = sumn / 2;
        
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));  //前i个数字 可以组成的最大数字

        for (int i = 1; i <= n; ++i) {
            int num = stones[i - 1];
            
            for (int j = target; j >= 0; --j) {
                if (j - num < 0) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j - num] + num);
                }
            }
        }

        return sumn - dp[n][target] * 2;   
    }
};

// 滚动数组优化
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        
        int sumn = accumulate(stones.begin(), stones.end(), 0);
        
        int target = sumn / 2;
        
        vector<int> dp(target + 1, 0);  //前i个数字 可以组成的最大数字

        for (int i = 1; i <= n; ++i) {
            int num = stones[i - 1];
            
            for (int j = target; j >= 0; --j) {
                if (j - num < 0) {
                    dp[j] = dp[j];
                } else {
                    dp[j] = max(dp[j], dp[j - num] + num);
                }
            }
        }

        return sumn - dp[target] * 2;   
    }
};