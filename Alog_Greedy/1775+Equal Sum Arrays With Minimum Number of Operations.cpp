class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sumn1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sumn2 = accumulate(nums2.begin(), nums2.end(), 0);

        if (sumn1 > sumn2) {
            return minOperations(nums2, nums1);
        }

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int i = 0, j = nums2.size() - 1;
        int cnt = 0;
        while (i < nums1.size() && j >= 0 && sumn1 < sumn2) {
            if (6 - nums1[i] > nums2[j] - 1) {  // nums1 小变大 缩进距离比 nums2 大变小 缩进的好
                sumn1 += (6 - nums1[i++]);
            } else {
                sumn2 -= (nums2[j--] - 1);
            }          
            cnt++;
        }   

        // 如果此时 sumn1 还是比 sumn2小. 看 i 和 j 还有哪个没遍历完，继续进行操作缩短两个sumn之间的差距
        while (i < nums1.size() && sumn1 < sumn2) {
            sumn1 += (6 - nums1[i++]);
            cnt++;
        }

        while (j >= 0 && sumn1 < sumn2) {
            sumn2 -= (nums2[j--] - 1);
            cnt++;
        }

        // 必须 sumn1 >= sumn2 时才能使数组的和相等 
        // 因为当大于的时候，说明最后一次加的差值过大了，完全可以加一个小一点的数，使 sumn1 == sumn2
        // 他都能让他大于了 肯定能加个小点的数让他等于了
        return sumn1 >= sumn2 ? cnt : -1;
    }
};