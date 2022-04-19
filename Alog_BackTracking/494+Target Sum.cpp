class Solution {
public:
    int cnt = 0;
    void bt(int target, vector<int> &nums, int i, int sumn) {
        if (i == nums.size()) {
            if (target == sumn) {
                cnt++;
            }
            return;
        }
        
        
        bt(target, nums, i+1, sumn+nums[i]);
        bt(target, nums, i+1, sumn-nums[i]);

        return;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        bt(target, nums, 0, 0);
        return cnt;
    }
};


