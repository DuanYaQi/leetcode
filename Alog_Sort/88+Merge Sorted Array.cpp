void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> tmp(nums1.size() + nums2.size(), 0);

    int i = 0, j = 0, index = 0;

    while (i < m && j < n) {
        if (nums1[i] < nums2[j]) tmp[index++] = nums1[i++];
        else tmp[index++] = nums2[j++];
    }

    while (i < m) tmp[index++] = nums1[i++];
    while (j < n) tmp[index++] = nums2[j++];

    for (int i = 0; i < index; ++i) nums1[i] = tmp[i];
}