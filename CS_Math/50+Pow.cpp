class Solution {
public:
    double quickPow(double x, long long N) {
        if (N == 0) return 1.0;

        double y = quickPow(x, N / 2);

        return N % 2 == 0 ? y * y : y * y * x;
    }
    double myPow(double x, int n) {
        long long N = n;

        return N >= 0 ? quickPow(x, N) : 1.0 / quickPow(x ,N);
    }
};