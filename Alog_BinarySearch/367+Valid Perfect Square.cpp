class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        if (num == 2 | num == 3) return false;

        int left = 0;
        int right = num / 2;
        int mid;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (pow(mid, 2) > num) {
                right = mid - 1;
            } else if (pow(mid, 2) < num) {
                left = mid + 1;
            } else {
                return true;
            }
        }

        return false;
    }
};