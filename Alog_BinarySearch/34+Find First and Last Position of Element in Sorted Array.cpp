// new
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftB = getLeftBorder(nums, target);
        int rightB = getRightBorder(nums, target);

        if (leftB > rightB) return {-1, -1};

        return {leftB, rightB};
    }

    int getLeftBorder(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] >= target) {
                hi = mid - 1;
            } else if (nums[mid] < target) {
                lo = mid + 1;
            }
        }

        return hi + 1;
    }

    int getRightBorder(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] > target) {
                hi = mid - 1;
            } else if (nums[mid] <= target) {
                lo = mid + 1;
            }
        }

        return lo - 1;
    }
    

};


class Solution {
public:
    int searchLeftBound(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        int leftBound = -2;

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = right - 1;
                leftBound = right;
            } else {
                left = mid + 1;
            }
        }
        return leftBound;
    }

    int searchRightBound(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        int rightBound = -2;

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
                rightBound = left;
            }
        }

        return rightBound;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = searchLeftBound(nums, target);
        int right = searchRightBound(nums, target);

        if (left == -2 || right == -2) 
            return {-1, -1};

        if (right - left > 1)
            return {left + 1, right - 1};

        return {-1, -1};


    }
};