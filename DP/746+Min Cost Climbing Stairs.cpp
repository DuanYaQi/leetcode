class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int N = cost.size();
        if (N < 2) return min(cost[0], cost[1]);
        
        vector<int> dp(N, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < N; ++i) { //从第二层开始
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        // 注意最后一步可以理解为不用花费,所以取倒数第一步,第二步的最少值
        return min(dp[N-1], dp[N-2]);
    }
};