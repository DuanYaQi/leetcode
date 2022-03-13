class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); ++fastIndex) {
            if (nums[fastIndex] == nums[slowIndex]) {
                continue;
            } else {
                nums[++slowIndex] = nums[fastIndex++];
            }
        }
        return slowIndex;
    }
};