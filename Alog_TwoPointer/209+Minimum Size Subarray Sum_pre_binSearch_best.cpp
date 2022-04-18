class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        vector<int> preSum(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            preSum[i+1] = preSum[i] + nums[i];
        }

        int res = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            int findT = preSum[i] + target;
            auto bound = lower_bound(preSum.begin(), preSum.end(), findT);
            if (bound != preSum.end()) { //如果存在
                int nLen = static_cast<int>((bound - preSum.begin()) - i);  // 第一个比findT大的数到i的位置
                res = min(res, nLen);
            }
        }        

        return res == INT_MAX ? 0 : res;
    }
};