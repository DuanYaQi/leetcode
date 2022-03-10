class Solution {
public:
    vector<int> res;

    void search(vector<int> &nums, int left, int right, int target) {
        int mid;

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                res.push_back(mid);
                search(nums, 0, mid - 1, target);
                search(nums, mid + 1, nums.size() - 1, target);
                    
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;   

        search(nums, left, right, target);

        if (res.size() != 0) {
            sort(res.begin(), res.end());
            return vector<int> {res[0], res[res.size()-1]};
        }

        return vector<int> {-1, -1};
    }
};