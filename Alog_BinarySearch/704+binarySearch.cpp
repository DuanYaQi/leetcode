int binartSearch(vector<int> &nums, int left, int right, int target) {
    int mid;
    while (left <= right) {
        mid = left + ((right - left) / 2); // 防止溢出 等同于(left + right)/2
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return -1;
}