class Solution {
public:
    int res = 1e9;

    void update(int sum, int target) {
        if (abs(sum - target) < abs(res - target)) {
            res = sum;
        }   
    }

    void findBThree(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int j = i + 1, k = nums.size() - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                update(sum, target);
                if (sum - target <= 0) {
                    j++;
                } else if (sum - target > 0) {
                    k--;                    
                }
            }
            
        }
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        findBThree(nums, target);

        return res;
    }
};