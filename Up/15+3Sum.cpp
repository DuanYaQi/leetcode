class Solution {
public:
    vector<vector<int>> res;

    void findThree(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i-1])  continue;

            int k = nums.size() - 1;
            for (int j = i + 1; j < k + 1; ++j) {
                if (j > i + 1 && nums[j] == nums[j-1]) continue;

                while (nums[i] + nums[j] + nums[k] > 0) k--;

                if (k <= j) break;
                if (nums[i] + nums[j] + nums[k] == 0) res.push_back({nums[i], nums[j], nums[k]});
            }
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        findThree(nums);
        return res;
    }
};