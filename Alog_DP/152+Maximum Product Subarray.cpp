class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size(); 

        vector<int> dpMax(n, 0);
        vector<int> dpMin(n, 0);

        dpMax[0] = nums[0];
        dpMin[0] = nums[0];

        int res = nums[0];
        for (int i = 1; i < n; ++i) {
            dpMax[i] = max(max(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]), nums[i]);
            dpMin[i] = min(min(dpMin[i-1] * nums[i], dpMax[i-1] * nums[i]), nums[i]);

            res = max(res, dpMax[i]);
        }

        return res;
    }
};