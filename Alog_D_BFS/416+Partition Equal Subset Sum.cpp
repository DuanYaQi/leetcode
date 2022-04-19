// 暴力
class Solution {
public:
    bool dfs(int i, int remain, vector<int>& nums) {
        if (remain == 0) return true;
        // target为负数 或 nums数组遍历完 返回false
        if (remain < 0 || i == nums.size()) return false;

        // 选这个数字   减这个数字
        bool b1 = dfs(i+1, remain - nums[i], nums);

        // 不选这个数字 不减这个数字
        bool b2 = dfs(i+1, remain, nums);

        return b1 || b2;    //注意这里是 || 有一条路可以满足就行
    }

    bool canPartition(vector<int>& nums) {
        int sumn = accumulate(nums.begin(), nums.end(), 0);

        if (sumn & 1) return false;

        return dfs(0, sumn / 2, nums);
    }
};

//记忆化搜索
class Solution {
public:
    bool dfs(int i, int remain, vector<int>& nums, vector<vector<int>> &memo) {
        if (remain == 0) return true;
        if (remain < 0 || i == nums.size()) return false;

        // 记忆化
        if (memo[i][remain] != -1) return memo[i][remain];
        memo[i][remain] = dfs(i+1, remain - nums[i], nums, memo) || dfs(i+1, remain, nums, memo);    //注意这里是 || 有一条路可以满足就行   

        /*
        // 选这个数字   减这个数字
        bool b1 = dfs(i+1, remain - nums[i], nums)
        // 不选这个数字 不减这个数字
        bool b2 = dfs(i+1, remain, nums);
        */

        return memo[i][remain];
    }

    bool canPartition(vector<int>& nums) {
        int sumn = accumulate(nums.begin(), nums.end(), 0);

        if (sumn & 1) return false;
        
        int target = sumn / 2;

        vector<vector<int>> memo(nums.size(), vector<int>(target + 1, -1)); //memo[i][j]里存出现过，就直接返回它的值

        return dfs(0, target, nums, memo);
    }    
};