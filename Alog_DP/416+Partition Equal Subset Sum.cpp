// 二维DP
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();

        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());

        if (sum & 1) return false;
        int target = sum / 2;
        if (maxNum > target) return false;

        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));    // 从下标i及之前的数字中选出若干个可以使得和为j

        for (int i = 0; i < n; ++i) // 从前 i 个数字中可以选出若干个使得其和为 0.   即不选任何数字即可得到 0.
            dp[i][0] = true;
        
        dp[0][nums[0]] = true;      // 前下标0及之前的数字中选出若干个,可以使得和为nums[0],即选中就好了
        for (int i = 1; i < n; ++i) {
            int num = nums[i];      // 当前重量
            for (int j = 0; j <= target; ++j) {
                if (j - num < 0) {    // 容量不够，无法选择第i个数字 nums[i-1]
                    dp[i][j] = dp[i-1][j];  // 不选, 跟上一个物品的状态一样
                } else {                    // 容量足够 选或者不选
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-num]; 
                }
            }
        }
        
        return dp[n-1][target];
    }
};


// 一维优化
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();

        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());

        if (sum & 1) return false;
        int target = sum / 2;
        if (maxNum > target) return false;

        vector<bool> dp(target + 1, false); 

        dp[0] = true;

        for (int i = 1; i < n; ++i) {
            int num = nums[i];        // 当前重量
            for (int j = target; j >= 0; --j) {	// 必须逆序，因为要保证 dp[j-num] 是前一时刻的
                if (j - num < 0) {    // 容量不够，无法选择第i个数字 nums[i-1]
                    dp[j] = dp[j];    // 不选, 跟上一个物品的状态一样   
                    // 后边这个dp[j]是前一时刻的值 即dp[i-1][j]
                } else {                    // 容量足够 选或者不选
                    dp[j] = dp[j] || dp[j-num]; 
                    // 后边这个dp[j] || dp[j-num] 是前一时刻的值 即dp[i-1][j] || dp[i-1][j-num]
                }
            }
        }

        return dp[target];
    }
};



class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();

        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());

        if (sum & 1) return false;
        int target = sum / 2;
        if (maxNum > target) return false;

        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        for (int i = 0; i <= n; ++i) // 示从前 i 个数字中可以选出若干个使得其和为 0.   即不选任何数字即可得到 0.
            dp[i][0] = true;
        

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= target; ++j) {
                if (j - nums[i-1] < 0) {    // 容量不够，无法选择第i个数字 nums[i-1]
                    dp[i][j] = dp[i-1][j];  // 不选, 跟上一个物品的状态一样
                } else {                    // 容量足够 选或者不选
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]]; 
                }
            }
        }
        
        return dp[n][target];
    }
};