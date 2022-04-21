class Solution {
public:
    int dfs(vector<int>& coins, int rem, vector<int> &memo) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;

        // 有记忆, 直接返回所需的最少硬币个数
        if (memo[rem] != -2) return memo[rem];    

        
        int minCnt = INT_MAX;
        for (int i = 0; i < coins.size(); ++i) {
            int cnt = dfs(coins, rem - coins[i], memo);
            if (cnt != -1 ) minCnt = min(cnt, minCnt);
        }

        memo[rem] = (minCnt == INT_MAX ? -1 : minCnt + 1);  //记忆化部分，通过数组记住金额为amount时，所需的最少硬币个数

        return memo[rem];
    }

    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, -2);    // memo[i]当前剩余金额为i时的最小选择硬币数
        int ans = dfs(coins, amount, memo);
        return ans == -2 ? -1 : ans;
    }
};