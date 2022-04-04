class Solution {
public:
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }


    int partition(vector<int>& nums, int lo, int hi) {
        int pivot = nums[lo], i = lo + 1, j = hi;

        while (i <= j) {
            while (i < hi && nums[i] <= pivot) i++;
            while (j > lo && nums[j] > pivot) j--;

            if (i >= j) break;
            swap(nums, i, j);
        }

        swap(nums, lo, j);
        return j;
    }

    void shuffle (vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            int r = i + rand() % (nums.size() - i);
            swap(nums, i, r);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        shuffle(nums);
        k = nums.size() - k;
        int lo = 0, hi = nums.size() - 1;
        

        while (1) {
            int p = partition(nums, lo, hi);

            if (p < k) {
                lo = p + 1;
            } else if (p > k) {
                hi = p - 1;
            } else {
                break;
            }
        }

        return nums[k];
    }
};