class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0;
        int size = nums.size() - 1;

        while (i <= size) {
            if (nums[i] == val) {
                nums[i] = nums[size];
                size--;
            } else {
                i++;
            }
        }
        return i;
    }
};