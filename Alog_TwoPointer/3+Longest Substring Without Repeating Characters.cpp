
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();

        int lo = 0, hi = lo;
        unordered_map<char, int> ump;

        int res = 0;
        for (; hi < n; ++hi) {
            ump[s[hi]]++;
            if (ump[s[hi]] == 1) {
                res = max(res, hi - lo + 1);
            } else {
                while (ump[s[hi]] != 1) {
                    ump[s[lo]]--;
                    lo++;
                }                
                res = max(res, hi - lo + 1);
            }
        }

        return res;
    }
};