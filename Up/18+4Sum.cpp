class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i-1]) continue;

            for (int j = i + 1; j < nums.size(); ++j) {
                if (j > i+1 && nums[j] == nums[j-1]) continue;

                int m = j + 1, n = nums.size() - 1;

                
                while (m < n) {
                    int sum = nums[i] + nums[j] + nums[m] + nums[n];
                    if (sum - target < 0) {
                        m++;
                    } else if (sum - target > 0) {
                        n--;
                    } else {
                        res.push_back({nums[i], nums[j], nums[m], nums[n]});
                        m++;
                        while(nums[m] == nums[m-1] && m < n) m++;
                    }
                }
            }
        }

        return res;
    }
};