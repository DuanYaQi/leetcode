class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;

        for (int i = 0; i < n; ++i) {
            if (i <= rightmost) {    // 当前节点是可以到达的
                rightmost = max(rightmost, i + nums[i]);
                
                if (rightmost >= n-1)
                    return true;
            }
        }

        return false;
    }
};