class Solution {
public:
    void quickSort(vector<int>& nums, int lo, int hi) {
        if (lo >= hi)  return;

        int p = partition(nums, lo, hi);
        
        quickSort(nums, lo, p - 1);
        quickSort(nums, p + 1, hi);
        return;
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

    void swap(vector<int>& nums, int a, int b) {
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }

    void shuffle(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0 ; i < n; i++) {
            // 生成 [i, n - 1] 的随机数
            int r = i + rand() % (n - i);
            swap(nums, i, r);
        }
    }

    void sortColors(vector<int>& nums) {
        
        shuffle(nums);
        quickSort(nums, 0, nums.size()-1);
    }
};