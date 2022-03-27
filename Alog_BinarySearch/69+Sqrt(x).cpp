int mySqrt(int x) {
    int left = 1, right = x;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if ((long long)mid * mid > x) {
            right = mid - 1;
        } else {
            left  = mid + 1; 
        } 
    }

    return left - 1;
}