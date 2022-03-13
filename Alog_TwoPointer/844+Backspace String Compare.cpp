class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int slowIndex = 0;

        for (int fastIndex = 0; fastIndex < s.size(); ++fastIndex) {
            if (s[fastIndex] == '#') {
                slowIndex = max(slowIndex -= 1, 0);
                s[slowIndex] = s[fastIndex];
            } else {
                s[slowIndex++] = s[fastIndex];
            }
        }

        int slowIndex1 = 0;

        for (int fastIndex = 0; fastIndex < t.size(); ++fastIndex) {
            if (t[fastIndex] == '#') {
                slowIndex1 = max(slowIndex1 - 1, 0);
                t[slowIndex1] = t[fastIndex];
            } else {
                t[slowIndex1++] = t[fastIndex];
            }
        }

        if (slowIndex != slowIndex1) {
            return false;
        }

        for (int i = 0; i < slowIndex; ++i) {
            if (s[i] != t[i]) {
                return false;
            }
        }

        return true;
    }