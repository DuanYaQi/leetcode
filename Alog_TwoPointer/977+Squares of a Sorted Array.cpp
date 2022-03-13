class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int start = 0;
        int end = nums.size() - 1;

        vector<int> res(end + 1);
        int site = end;

        while (site >= 0) {
            if (nums[start] * nums[start] > nums[end] * nums[end]) {
                res[site--] = nums[start] * nums[start];
                start++;
            } else {
                res[site--] = nums[end] * nums[end];
                end--;
            }
        }

        return res;
    }
};