class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> preSum(n + 1, 0);
        unordered_map<int, int> ump;// 存前缀和的值 后边的和减去前边的和 = k 说明也满足条件

        ump[0] = 1; // 这一行的作用就是为了应对 nums[0] +nums[1] + ... + nums[i] == k 的情况的, 也就是从下标 0 累加到下标 i
        
        // 如果不加这个就是算 nums[1] + ... + nums[i] == k
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            preSum[i] = preSum[i-1] + nums[i-1];

            cnt += ump[preSum[i] - k];
            ump[preSum[i]]++;	    
        }

        return cnt;
    } 
};