class Solution {
public:
    pair<int, int> getMaxString(string &s, int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) {
            l--;
            r++;
        }
        return {l + 1, r - 1};
    }

    string longestPalindrome(string s) {
        n = s.size();
        int lres, rres;
        int maxL = -1;
        for (int i = 0; i < n; ++i) {
            auto p1 = getMaxString(s, i, i);
            auto p2 = getMaxString(s, i, i + 1);
            int nowL = p1.second - p1.first;
            if (maxL < nowL) {
                maxL = nowL;
                lres = p1.first, rres = p1.second;
            }

            nowL = p2.second - p2.first;
            if (maxL < nowL) {
                maxL = nowL;
                lres = p2.first, rres = p2.second;
            }
        }
        
        return s.substr(lres, rres - lres + 1);
    }
private:
    int n;
};