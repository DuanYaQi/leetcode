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


bool canJump(vector<int>& nums) {
    int n = nums.size();
    int maxI = 0;

    for (int i = 0; i < n; ++i) {
        if (i <= maxI) {
            maxI = max(maxI, i + nums[i]);
        } else {			// 中途走不动了，说明到达不了
            return false;
        }            
    }

    return true;
}