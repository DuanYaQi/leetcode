class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int count = 0;
        int res = INT_MIN;

        for (int i = 0; i < nums.size(); ++i) {
            count += nums[i];
            res = max(res, count);
            if (count < 0) count = 0;
        }
        
        return res;
    }
};