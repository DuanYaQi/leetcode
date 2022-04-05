class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> ump;
        int i = 0, j = nums.size() - 1;

        for (int i = 0; i < nums.size(); ++i) {
            if (ump.find(target - nums[i]) != ump.end()) {
                return {i, ump[target - nums[i]]};
            }
            
            ump[nums[i]] = i;
        }   
        return {};
    }
};