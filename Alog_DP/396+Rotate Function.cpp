class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();

        int sumn = accumulate(nums.begin(), nums.end(), 0);

        vector<int> F(n, 0);
        for (int i = 0; i < n; ++i) {
            F[0] += (i * nums[i]);
        }

        
        for (int i = 1; i < n; ++i) {
            F[i] = F[i-1] + sumn - n * nums[n-i];
        }

        return *max_element(F.begin(), F.end());
    }
};