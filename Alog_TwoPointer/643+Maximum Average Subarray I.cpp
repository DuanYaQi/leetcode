class Solution {
public:
    bool check(vector<int>& nums, double mid, int k) {
        int n = nums.size();
        vector<double> preSum(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            preSum[i] = preSum[i-1] + nums[i-1] - mid;
        }
        

        for (int i = k; i <= n; ++i) {
            if (preSum[i] - preSum[i-k] >= 0) return true;
        }

        return false;
    }

    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double maxV = *max_element(nums.begin(), nums.end());
        double minV = *min_element(nums.begin(), nums.end());

        while (maxV - minV > 1e-5) {
            double mid = minV + (maxV - minV) / 2;
            if (check(nums, mid, k)) {
                minV = mid;
            } else {    // 不满足说明值太大，所以maxV变小为mid
                maxV = mid;
            }
        }

        return minV;
    }
};