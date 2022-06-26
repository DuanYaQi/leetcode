class Solution {
    vector<int> &nums;
public:
    Solution(vector<int> &nums) : nums(nums) {}

    int pick(int target) {
        int result;
        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                if (rand() % ++count == 0) {
                    result = i;
                }
            }
        }
        return result;
    }
};