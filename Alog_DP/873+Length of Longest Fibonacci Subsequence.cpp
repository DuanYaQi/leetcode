class Solution {
public:
    // dp[j][k] 表示在以第j和第k为子序列的后两位时，能找到的最长子序列的长度
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) { // 必须保证 j < k
                int iNum = arr[k] - arr[j];
                auto it = lower_bound(arr.begin(), arr.end(), iNum);
                if (it != arr.end() && *it == iNum) {
                    int i = it - arr.begin();
                    if (i < j)  // 必须要保证 i < j
                        dp[j][k] = max(dp[i][j] + 1, 3);
                }
            }
        }

        int res = 0;
        for (auto &oneD : dp)
            for (auto &num : oneD)
                res = max(res, num);

        return res;
    }
};