class Solution {
public:
    void quickSort(vector<int>& nums, int lo, int hi) {
        if (lo >= hi) return;

        int p = partition(nums, lo, hi);

        quickSort(nums, lo, p - 1);
        quickSort(nums, p + 1, hi);
    }


    int partition(vector<int>& nums, int lo, int hi) {
        int pivot = nums[lo];
        int i = lo + 1, j = hi;

        while (i <= j) {
            while (j > lo && nums[j] >= pivot) j--;
            while (i < hi && nums[i] < pivot) i++;

            if (i >= j) break;
            swap(nums, i, j);
        }

        swap(nums, lo, j);
        return j;
    }


    void swap(vector<int>& nums, int x, int y) {
        int tmp = nums[x];
        nums[x] = nums[y];
        nums[y] = tmp;
    }

    void shuffle(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int r = i + rand() % (n - i);
            swap(nums, i, r);
        }
    }


    vector<int> sortArray(vector<int>& nums) {
        shuffle(nums);
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};