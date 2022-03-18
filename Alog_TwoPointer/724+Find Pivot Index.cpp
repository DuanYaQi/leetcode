class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int presum[nums.size() + 1];
        presum[0] = 0;

        for (int i = 0; i < nums.size(); ++i) {
            presum[i + 1] = nums[i] + presum[i];
        }

        int left = 0, right = 0;
        for (int i = 0; i < nums.size(); ++i) {
            left = presum[i] - presum[0];
            right = presum[nums.size()] - presum[i];

            if (left == right) {
                return i;
            }

        }
        return -1;
    }
};