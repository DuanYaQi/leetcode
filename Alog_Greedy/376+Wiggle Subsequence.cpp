class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        int preDiff = 0;
        int curDiff = 0;
        int result = 1;

        for (int i = 1; i < n; ++i) {
            curDiff = nums[i] - nums[i-1];
            if ((curDiff > 0 && preDiff <= 0) || (curDiff < 0 && preDiff >= 0)) {
                result++;
                preDiff = curDiff;
            }
        }

        return result;
    }
};