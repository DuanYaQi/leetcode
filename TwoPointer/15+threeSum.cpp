class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        int left,right;

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }

            left = i + 1;
            right = nums.size() - 1;

            while (left < right) {
                if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                } else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                } else {
                    // 找到答案时，双指针同时收缩
                    res.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    right--;
                    left++;

                    // 去重复值
                    while (right > left && nums[right] == nums[right + 1]) {
                        right--;
                    }
                    while (right > left && nums[left] == nums[left - 1]) {
                        left++;
                    }

                    
                }
            }
        }
        return res;
    }
};