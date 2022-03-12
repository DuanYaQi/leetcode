int mySqrt(int x) {
    int left = 1;  
    int right = x;
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (pow(mid, 2) > x) {
            right = mid - 1;
        } else {
            left  = mid + 1; 
        } 
    }

    return left - 1;
}