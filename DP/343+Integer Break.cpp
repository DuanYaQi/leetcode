class Solution {
public:
    int integerBreak(int n) {
        int dp[n+1];
        int a, b;
        int nmax = 0;
        int sumx = 0;
        for (int i = 2; i <= n; ++i) {
            a = n / i;
            b = n % i;
            
            sumx = a;
            if (b == 0) {
                for (int j = 0; j < i-1; ++j) {
                    sumx *= a;
                }
            } else {
                for (int j = 0; j < b; ++j) {
                    sumx *= a+1;
                }   
            }

            
 
            dp[i] = a;
            if (a > nmax)
                nmax = a;
        }

        return nmax;        
    }
};