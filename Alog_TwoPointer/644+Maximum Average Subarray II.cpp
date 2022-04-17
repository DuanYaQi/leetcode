644. 子数组最大平均数 II
给你一个包含 n 个整数的数组 nums ，和一个整数 k 。

请你找出 长度大于等于 k 且含最大平均值的连续子数组。并输出这个最大平均值。任何计算误差小于 10-5 的结果都将被视为正确答案。


示例 1：

输入：nums = [1,12,-5,-6,50,3], k = 4
输出：12.75000
解释：
- 当长度为 4 的时候，连续子数组平均值分别为 [0.5, 12.75, 10.5] ，其中最大平均值是 12.75 。
- 当长度为 5 的时候，连续子数组平均值分别为 [10.4, 10.8] ，其中最大平均值是 10.8 。
- 当长度为 6 的时候，连续子数组平均值分别为 [9.16667] ，其中最大平均值是 9.16667 。
当取长度为 4 的子数组（即，子数组 [12, -5, -6, 50]）的时候，可以得到最大的连续子数组平均值 12.75 ，所以返回 12.75 。
根据题目要求，无需考虑长度小于 4 的子数组。
示例 2：

输入：nums = [5], k = 1
输出：5.00000
 

提示：

n == nums.length
1 <= k <= n <= 104
-104 <= nums[i] <= 104



class Solution {
public:
    bool check(vector<int> nums, double mid, int k) {
        int n = nums.size();
        vector<double> preSum(n + 1, 0);    // 存储从第k个位置开始的累加和
        
        for (int i = 1; i <= n; ++i) 
            preSum[i] = preSum[i-1] + nums[i-1] - mid;
        
        
        double preMin = 0;
        for (int i = k; i <= n; ++i) {
            if (preSum[i] - preMin >= 0) return true; // 满足条件意味着 sum - minSum 这一部分的元素和大于0，即可以满足mid为平均值时
            preMin = min(preMin, preSum[i - k + 1]);  // minSum 记录最小preSum[i - k + 1]
        }
        
        return false;
    }

    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        
        double maxV = *max_element(nums.begin(), nums.end());
        double minV = *min_element(nums.begin(), nums.end());
        
        while ((maxV - minV) >= 1e-5) {
            double mid = (maxV + minV) / 2;
            if (check(nums, mid, k)) {  // 如果存在长度 >= k 的子数组之和 >= 0
                minV = mid;
            } else {                    // 不满足说明值太大，所以maxV变小为mid
                maxV = mid;
            }
        }
        
        return minV;
    }
};