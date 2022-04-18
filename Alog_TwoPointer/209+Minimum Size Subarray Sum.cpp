
/***************优化后*********************/
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        int i = 0;

        int sum = 0, res = INT_MAX;
        for (int j = i; j < nums.size(); ++j) {
            sum += nums[j];

            if (sum >= target) {
                while (sum - nums[i] >= target) {
                    sum -= nums[i];           // 一定要先减 再移动左边窗口起点位置         
                    i++;
                }
                res = min(res, j-i+1);
            }
        }
 
        return res == INT_MAX ? 0 : res;
    }
};


/***************优化后*********************/
