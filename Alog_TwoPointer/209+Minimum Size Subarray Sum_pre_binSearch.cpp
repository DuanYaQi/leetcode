class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        vector<int> preSum(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            preSum[i+1] = preSum[i] + nums[i];
        }

        int res = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            int lo = 0, hi = i;

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (preSum[i] - preSum[mid] >= target) {
                    res = min(res, i - mid);
                    lo = mid + 1;          
                } else {
                    hi = mid - 1; 
                }
            }
        }        

        return res == INT_MAX ? 0 : res;
    }
};