const int maxn = 5e4 + 10;

class Solution {
public: 
    void merge(vector<int>& nums, int l1, int r1, int l2, int r2) {
        int i = l1, j = l2, index = 0;
        int tmp[maxn];
        
        while (i <= r1 && j <= r2) {
            if (nums[i] < nums[j]) tmp[index++] = nums[i++];
            else tmp[index++] = nums[j++];
        }
        
        while (i <= r1) tmp[index++] = nums[i++];
        while (j <= r2) tmp[index++] = nums[j++];
        
        for (int i = 0; i < index; ++i) nums[l1+i] = tmp[i];
    }

    void mergeSort(vector<int>& nums, int lo, int hi) {
        if (lo == hi) return;

        int mid = lo + (hi - lo) / 2;

        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);

        merge(nums, lo, mid, mid+1, hi);
    }

    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size()-1);
        return nums;
    }
};