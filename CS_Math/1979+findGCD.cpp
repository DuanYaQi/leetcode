class Solution {
public:
    int gcd(int a, int b) {
        if (b == 0) return a;

        return gcd(b, a % b);
    }

    int findGCD(vector<int>& nums) {
        int maxn = *max_element(nums.begin(), nums.end());
        int minn = *min_element(nums.begin(), nums.end());

        return gcd(maxn, minn);
    }
};