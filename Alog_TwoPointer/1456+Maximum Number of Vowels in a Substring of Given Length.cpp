class Solution {
public:
    inline bool isVowel(char c) {
        return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
    }

    int maxVowels(string s, int k) {
        int n = s.size();
        
        int res = 0, cnt = 0;
        int lo = 0, hi = 0;
        for (; hi < k; ++hi) {
            if (isVowel(s[hi])) {
                cnt++;
            }
        }
        
        res = cnt;

        for (; hi < n; ++lo, ++hi) {
            if (isVowel(s[lo])) {
                cnt--;
            }

            if (isVowel(s[hi])) {
                cnt++;
            }

            res = max(res, cnt);
        }

        return res;
    }
};