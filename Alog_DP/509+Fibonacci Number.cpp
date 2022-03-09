class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }
};


class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        vector<int> dp(3);
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[2] = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = dp[2];            
        }

        return dp[2];
    }
};

//best array cost less space than vector
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        int dp[3];
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            dp[2] = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = dp[2];            
        }

        return dp[2];
    }
};