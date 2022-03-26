class Solution {
public:
    int countHillValley(vector<int>& nums) {
        vector<int> v;
        for (int x : nums)
            if (v.empty() or v.back() != x) v.push_back(x);
        int res = 0;
        for (int i = 1; i + 1 < v.size(); i += 1) {
            res += (v[i] - v[i - 1]) * (v[i] - v[i + 1]) > 0;
        }
        return res;
    }
};